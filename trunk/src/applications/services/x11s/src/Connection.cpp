// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <OEG/Common.h>

#include <QByteArray>
#include <QTcpSocket>
#include <QSysInfo>

#include "Server.h"
#include "Keyboard.h"
#include "Connection.h"

Connection::Connection(QTcpSocket *socket, Server *server)
 : QObject(0), m_socket(socket), m_server(server)
{
  if (! m_socket) {
    qDebug() << "No socket.";
    return;
  }

  if (! m_server) {
    qDebug() << "No server.";
    return;
  }

  m_byte_order      = QDataStream::BigEndian;              // Most significant byte first (the default).
  m_sequence_number = 0;
}

Connection::~Connection()
{
  qDebug() << "Connection::~Connection()";

  if (m_socket) {
    if (m_socket->isValid()) {
      m_socket->disconnectFromHost();
      qDebug() << "  disconnectFromHost()";
      if (m_socket->state() != QAbstractSocket::UnconnectedState) {  // NEEDED?
        qDebug() << "  Not UnconnectedState: wait for dc.";
        m_socket->waitForDisconnected(1000);
      }
    }
    //delete m_socket; m_socket = 0;
  }
}

void Connection::init()
{
  connect(m_socket, SIGNAL(disconnected()),
          m_socket, SLOT(deleteLater()));
  connect(m_socket, SIGNAL(disconnected()),
          this,     SLOT(emitDisconnected()));
  connect(m_socket, SIGNAL(readyRead()),
          this,     SLOT(onReadyRead()));

  //const int timeout = 3 * 1000;
  quint16 s;

  readByteOrder();
  readByte();                                              // Unused.
  s = readShort();   // Protocol major version.
  qDebug() << "Protocol major version: " << s;
  s = readShort();   // Protocol minor version.
  qDebug() << "Protocol minor version: " << s;

  int nameLength = readShort();
  int dataLength = readShort();
  readShort();                                             // Unused.

  if (nameLength > 0) {
    readOmit(nameLength);                                  // Authorization protocol name.
    readOmit(-nameLength & 3);	                           // Padding.
  }

  if (dataLength > 0) {
    readOmit(dataLength);                                  // Authorization protocol data.
    readOmit(-dataLength & 3);                             // Padding.
  }

  QByteArray vendor(Server::m_vendor.toLatin1());
  int pad = -1 * vendor.length() & 3;
  int extra = 26 + 2 * m_server->getNumberOfPixmapFormats() + (vendor.length() + pad) / 4;

  Keyboard *keyboard = m_server->getKeyboard();

  writeByte(1);                                            // Success.
  writeByte(0);                                            // Unused.
  writeShort(Server::m_protocol_major_version);
  writeShort(Server::m_protocol_minor_version);
  writeShort(extra);                                       // Length of data.
  writeInt(Server::m_release_number);                      // Release number.
  writeInt(m_resource_id_base);
  writeInt(m_resource_id_mask);
  writeInt(0);                                             // Motion buffer size.
  writeShort(vendor.length());                             // Vendor length.
  writeShort(0xffff);                                      // Max request length.
  writeByte(1);                                            // Number of screens.
  writeByte(m_server->getNumberOfPixmapFormats());
  writeByte(0);                                            // Image byte order (0=LSB, 1=MSB).
  writeByte(1);                                            // Bitmap bit order (0=LSB, 1=MSB).
  writeByte(8);                                            // Bitmap format scanline unit.
  writeByte(8);                                            // Bitmap format scanline pad.
  writeByte(keyboard->minimumKeycode());
  writeByte(keyboard->maximumKeycode());
  writePaddingBytes(4);                                    // Unused.

  if (vendor.length() > 0) {                               // Write padded vendor string.
    writeBytes(vendor);
    writePaddingBytes(pad);
  }

  m_server->writeFormats(this);
  //m_server->getScreen().write(_inputOutput);

  flush();



}

// Is client connected and the connection valid?

bool Connection::isValid()
{
  if (! m_socket)
    return false;

  if (! m_socket->isValid())
    return false;

  if (m_socket->state() == QAbstractSocket::UnconnectedState)
    return false;

  return true;
}

void Connection::onReadyRead()
{
  qDebug() << "onReadyRead().";

  if (! m_socket->bytesAvailable()) {
    qDebug() << "onReadyRead(): No bytes available.";
    return;
  }
  qDebug() << "onReadyRead(): " << m_socket->bytesAvailable();

  //QByteArray data = m_socket->readAll();
  //m_socket->write(data);
  //qDebug() << data;
}

void Connection::emitDisconnected()
{
  emit disconnected(this);
}

// Reads an 8-bit integer (0 to 255) from the input stream.

quint8 Connection::readByte()
{
  if (m_socket->bytesAvailable() < 1) {
    qDebug() << "Connection::readByte(): waiting for data";
    if (! m_socket->waitForReadyRead()) {  // set own timeout here
      // emit error(socket.error(), socket.errorString());
    }
  }

  char c;
  if (m_socket->read(&c, 1) == -1)
    qDebug() << "Connection::readByte(): read failed.";

  return c;
}

// Reads an 16-bit integer (0 to 65535) from the input stream.

quint16 Connection::readShort()
{
  quint8 i = readByte();

  if (m_byte_order == QDataStream::BigEndian)
    return (i << 8) | readByte();

  return i | (readByte() << 8);
}

// Reads an 32-bit signed integer from the input stream.

qint32 Connection::readInt()
{
  qint32 i = readByte();

  if (m_byte_order == QDataStream::BigEndian) {
    i = (i << 8) | readByte();
    i = (i << 8) | readByte();
    i = (i << 8) | readByte();
  } else {
    i = i | readByte() <<  8;
    i = i | readByte() << 16;
    i = i | readByte() << 24;
  }

  return i;
}

// Ignore next count bytes and skip over them.

void Connection::readOmit(int count)
{
  for (int i=0; i<count; i++)
    readByte();
}

// Parses the byte ordering information.

void Connection::readByteOrder()
{
  int byteOrder = readByte();

  if (byteOrder == 0x42)
    m_byte_order = QDataStream::BigEndian;
  else if (byteOrder == 0x6c)
    m_byte_order = QDataStream::LittleEndian;
  else
    qDebug() << "Connection::readByteOrder(): unknown byteorder: " << byteOrder;
}

// Empty buffers of all streams.

void Connection::flush()
{
  m_socket->waitForBytesWritten();
}

// Writes an 8-bit integer to the output stream.

void Connection::writeByte(quint8 data)
{
  char c = data;

  if (m_socket->write(&c, 1) == -1)
    qDebug() << "Connection::writeByte(quint8 data): write failed.";
}

// Write an array of bytes to the output stream.

void Connection::writeBytes(const QByteArray &array)
{
  if (m_socket->write(array.constData(), array.size()) == -1)
    qDebug() << "Connection::writeBytes(bytearray): write failed.";
}

// Writes a 16-bit integer to the output stream.

void Connection::writeShort(quint16 data)
{
  if (m_byte_order == QDataStream::BigEndian) {
    writeByte((data >> 8) & 0xff);
    writeByte((data)      & 0xff);
  } else {
    writeByte((data)      & 0xff);
    writeByte((data >> 8) & 0xff);
  }
}

// Writes a 32-bit integer to the output stream.

void Connection::writeInt(qint32 data)
{
  if (m_byte_order == QDataStream::BigEndian) {
    writeByte((data >> 24) & 0xff);
    writeByte((data >> 16) & 0xff);
    writeByte((data >>  8) & 0xff);
    writeByte((data)       & 0xff);
  } else {
    writeByte((data)       & 0xff);
    writeByte((data >>  8) & 0xff);
    writeByte((data >> 16) & 0xff);
    writeByte((data >> 24) & 0xff);
  }
}

// Writes count padding bytes to the output stream.

void Connection::writePaddingBytes(int count)
{
  for (int i=0; i<count; i++)
    writeByte(0);
}

// Writes the header of a X11 reply. The argument is optional.

void Connection::writeReplyHeader(int argument)
{
  writeByte(1);	                                           // Reply.
  writeByte(argument);
  writeShort(sequenceNumber() & 0xffff);
}

// Counts the bits in an integer.

quint8 Connection::countBits(quint32 data)
{
  quint8 count = 0;

  while (data > 0) {
    if (data & 1)
      count++;
    data >>= 1;
  }

  return count;
}

// Get the sequence number of the latest request sent by the client.

int Connection::sequenceNumber ()
{
  return m_sequence_number;
}

