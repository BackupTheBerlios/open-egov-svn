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

#include <QTcpSocket>
#include <QSysInfo>

#include "Connection.h"

Connection::Connection(QTcpSocket *socket)
 : QObject(0), m_socket(socket)
{
  if (! m_socket) {
    qDebug() << "No socket.";
    return;
  }

  m_byte_order      = QDataStream::BigEndian;              // Most significant byte first (the default).
  m_sequence_number = 0;

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
  readShort();      // Unused.

  if (nameLength > 0) {
    readOmit(nameLength);    // Authorization protocol name.
    readOmit(-nameLength & 3);	// Padding.
  }

  if (dataLength > 0) {
    readOmit(dataLength);    // Authorization protocol data.
    readOmit(-dataLength & 3);   // Padding.
  }



}

Connection::~Connection()
{
  if (m_socket) {
    if (m_socket->isValid()) {
      m_socket->disconnectFromHost();
      if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->waitForDisconnected(1000);
      }
    }
    delete m_socket; m_socket = 0;
  }
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

//

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

// Counts the bits of an integer.

quint8 Connection::countBits(quint32 data)
{
  quint8 count = 0;

  while (data > 0) {
    if (data & 1)
      count ++;
    data >>= 1;
  }

  return count;
}

// Get the sequence number of the latest request sent by the client.

int Connection::sequenceNumber ()
{
  return m_sequence_number;
}

