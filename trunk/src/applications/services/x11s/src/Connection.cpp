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

#include "Error.h"
#include "Event.h"
#include "Request.h"
#include "Window.h"

#include "Server.h"
#include "Keyboard.h"
#include "Connection.h"

Connection::Connection(QTcpSocket *socket, Server *server)
 : QObject(0), m_socket(socket), m_server(server)
{
  qDebug() << "Connection::Connection()";

  if (! m_socket) {
    qDebug() << "No socket.";
    return;
  }

  if (! m_server) {
    qDebug() << "No server.";
    return;
  }

  QObject::connect(socket, SIGNAL(disconnected()),
                   socket, SLOT(deleteLater()));

  m_close_connection = false;                              // Connection is initially open.
  m_byte_order       = QDataStream::BigEndian;             // Most significant byte first (the default).
  m_sequence_number  = 0;
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
  int extra = 26 + 2 * m_server->numberOfPixmapFormats() + (vendor.length() + pad) / 4;

  Keyboard *keyboard = m_server->keyboard();

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
  writeByte(m_server->numberOfPixmapFormats());
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

// Waits for client requests, parses and handles them.

void Connection::loop()
{
  quint8  opcode;
  quint8  argument;
  quint16 remaining;

  while (! m_close_connection) {
    opcode    = readByte();                                 // Request's opcode.
    argument  = readByte();                                 // Request's optional first argument (data).
    remaining = readShort() * 4 - 4;                        // Request's length -> remaining bytes.

    while (! m_server->processingAllowed(this))             // Wait if server was grabbed.
      ;//sleep(50);

    m_sequence_number++;                                    // Processing next request.

    switch (opcode) {                                       // Handle the request.
      case Request::XRQ_CREATE_WINDOW:                      // Page: 44.
        Window::requestCreateWindow(this);
        break;

      case Request::XRQ_CHANGE_WINDOW_ATTRIBUTE:            // Page: 
        Window::requestChangeWindowAttribute(this);
        break;

      case Request::XRQ_GET_WINDOW_ATTRIBUTES:              // Page: 
        Window::requestGetWindowAttributes(this);
        break;

      case Request::XRQ_DESTROY_WINDOW:                     // Page: 47.
        Window::requestDestroyWindow(this);
        break;

      case Request::XRQ_DESTROY_SUBWINDOWS:                 // Page: 
        Window::requestDestroySubWindows(this);
        break;

      case Request::XRQ_CHANGE_SAVE_SET:
        break;

      case Request::XRQ_REPARENT_WINDOW:
        break;

      case Request::XRQ_MAP_WINDOW:
        break;

      case Request::XRQ_MAP_SUBWINDOWS:
        break;

      case Request::XRQ_UNMAP_WINDOW:
        break;

      case Request::XRQ_UNMAP_SUBWINDOWS:
        break;

      case Request::XRQ_CONFIGURE_WINDOW:
        break;

      case Request::XRQ_CIRCULATE_WINDOW:
        break;

      case Request::XRQ_GET_GEOMETRY:
        break;

      case Request::XRQ_QUERY_TREE:
        break;

      case Request::XRQ_INTERN_ATOM:
        break;

      case Request::XRQ_GET_ATOM_NAME:
        break;

      case Request::XRQ_CHANGE_PROPERTY:
        break;

      case Request::XRQ_DELETE_PROPERTY:
        break;

      case Request::XRQ_GET_PROPERTY:
        break;

      case Request::XRQ_LIST_PROPERTIES:
        break;

      case Request::XRQ_SET_SELECTION_OWNER:
        break;

      case Request::XRQ_GET_SELECTION_OWNER:
        break;

      case Request::XRQ_CONVERT_SELECTION:
        break;

      case Request::XRQ_SEND_EVENT:
        break;

      case Request::XRQ_GRAB_POINTER:
        break;

      case Request::XRQ_UNGRAB_POINTER:
        break;

      case Request::XRQ_GRAB_BUTTON:
        break;

      case Request::XRQ_UNGRAB_BUTTON:
        break;

      case Request::XRQ_CHANGE_ACTIVE_POINTER_GRAB:
        break;

      case Request::XRQ_GRAB_KEYBOARD:
        break;

      case Request::XRQ_UNGRAB_KEYBOARD:
        break;

      case Request::XRQ_GRAB_KEY:
        break;

      case Request::XRQ_UNGRAB_KEY:
        break;

      case Request::XRQ_ALLOW_EVENTS:
        break;

      case Request::XRQ_GRAB_SERVER:
        break;

      case Request::XRQ_UNGRAB_SERVER:
        break;

      case Request::XRQ_QUERY_POINTER:
        break;

      case Request::XRQ_GET_MOTION_EVENTS:
        break;

      case Request::XRQ_TRANSLATE_COORDINATES:
        break;

      case Request::XRQ_WARP_POINTER:
        break;

      case Request::XRQ_SET_INPUT_FOCUS:
        break;

      case Request::XRQ_GET_INPUT_FOCUS:
        break;

      case Request::XRQ_QUERY_KEYMAP:
        break;

      case Request::XRQ_OPEN_FONT:
        break;

      case Request::XRQ_CLOSE_FONT:
        break;

      case Request::XRQ_QUERY_FONT:
        break;

      case Request::XRQ_QUERY_TEXT_EXTENTS:
        break;

      case Request::XRQ_LIST_FONTS:
        break;

      case Request::XRQ_LIST_FONTS_WITH_INFO:
        break;

      case Request::XRQ_SET_FONT_PATH:
        break;

      case Request::XRQ_GET_FONT_PATH:
        break;

      case Request::XRQ_CREATE_PIXMAP:
        break;

      case Request::XRQ_FREE_PIXMAP:
        break;

      case Request::XRQ_CREATE_GC:
        break;

      case Request::XRQ_CHANGE_GC:
        break;

      case Request::XRQ_COPY_GC:
        break;

      case Request::XRQ_SET_DASHES:
        break;

      case Request::XRQ_SET_CLIP_RECTANGLES:
        break;

      case Request::XRQ_FREE_GC:
        break;

      case Request::XRQ_CLEAR_AREA:
        break;

      case Request::XRQ_COPY_AREA:
        break;

      case Request::XRQ_COPY_PLANE:
        break;

      case Request::XRQ_POLY_POINT:
        break;

      case Request::XRQ_POLY_LINE:
        break;

      case Request::XRQ_POLY_SEGMENT:
        break;

      case Request::XRQ_POLY_RECTANGLE:
        break;

      case Request::XRQ_POLY_ARC:
        break;

      case Request::XRQ_FILL_POLY:
        break;

      case Request::XRQ_POLY_FILL_RECTANGLE:
        break;

      case Request::XRQ_POLY_FILL_ARC:
        break;

      case Request::XRQ_PUT_IMAGE:
        break;

      case Request::XRQ_GET_IMAGE:
        break;

      case Request::XRQ_POLY_TEXT_8:
        break;

      case Request::XRQ_POLY_TEXT_16:
        break;

      case Request::XRQ_IMAGE_TEXT_8:
        break;

      case Request::XRQ_IMAGE_TEXT_16:
        break;

      case Request::XRQ_CREATE_COLORMAP:
        break;

      case Request::XRQ_FREE_COLORMAP:
        break;

      case Request::XRQ_COPY_COLORMAP_AND_FREE:
        break;

      case Request::XRQ_INSTALL_COLORMAP:
        break;

      case Request::XRQ_UNINSTALL_COLORMAP:
        break;

      case Request::XRQ_LIST_INSTALLED_COLORMAPS:
        break;

      case Request::XRQ_ALLOC_COLOR:
        break;

      case Request::XRQ_ALLOC_NAMED_COLOR:
        break;

      case Request::XRQ_ALLOC_COLOR_CELLS:
        break;

      case Request::XRQ_ALLOC_COLOR_PLANES:
        break;

      case Request::XRQ_FREE_COLORS:
        break;

      case Request::XRQ_STORE_COLORS:
        break;

      case Request::XRQ_STORE_NAMED_COLOR:
        break;

      case Request::XRQ_QUERY_COLORS:
        break;

      case Request::XRQ_LOOKUP_COLOR:
        break;

      case Request::XRQ_CREATE_CURSOR:
        break;

      case Request::XRQ_CREATE_GLYPH_CURSOR:
        break;

      case Request::XRQ_FREE_CURSOR:
        break;

      case Request::XRQ_RECOLOR_CURSOR:
        break;

      case Request::XRQ_QUERY_BEST_SIZE:
        break;

      case Request::XRQ_QUERY_EXTENSION:
        break;

      case Request::XRQ_LIST_EXTENSIONS:
        break;

      case Request::XRQ_CHANGE_KEYBOARD_MAPPING:
        break;

      case Request::XRQ_GET_KEYBOARD_MAPPING:
        break;

      case Request::XRQ_CHANGE_KEYBOARD_CONTROL:
        break;

      case Request::XRQ_GET_KEYBOARD_CONTROL:
        break;

      case Request::XRQ_BELL:
        break;

      case Request::XRQ_CHANGE_POINTER_CONTROL:
        break;

      case Request::XRQ_GET_POINTER_CONTROL:
        break;

      case Request::XRQ_SET_SCREEN_SAVER:
        break;

      case Request::XRQ_GET_SCREEN_SAVER:
        break;

      case Request::XRQ_CHANGE_HOSTS:
        break;

      case Request::XRQ_LIST_HOSTS:
        break;

      case Request::XRQ_SET_ACCESS_CONTROL:
        break;

      case Request::XRQ_SET_CLOSE_DOWN_MODE:
        break;

      case Request::XRQ_KILL_CLIENT:
        break;

      case Request::XRQ_ROTATE_PROPERTIES:
        break;

      case Request::XRQ_FORCE_SCREEN_SAVER:
        break;

      case Request::XRQ_SET_POINTER_MAPPING:
        break;

      case Request::XRQ_GET_POINTER_MAPPING:
        break;

      case Request::XRQ_SET_MODIFIER_MAPPING:
        break;

      case Request::XRQ_GET_MODIFIER_MAPPING:
        break;

      case Request::XRQ_NO_OPERATION:
        break;

      default:                                              // Opcode not implemented.
        qDebug() << "Connection::loop(): opcode not implemented.";
        readOmit(remaining);
        Error::writeError(this, Error::XEC_IMPLEMENTATION, (Request::RequestOpcode) opcode);
        break;
    }
  }
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

