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

#include "Server.h"
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

QByteArray data = m_socket->readAll();
m_socket->write(data);
qDebug() << data;
}

void Connection::emitDisconnected()
{
  emit disconnected(this);
}

// Empty buffers of all streams.

void Connection::flush()
{
  m_socket->waitForBytesWritten();
}

