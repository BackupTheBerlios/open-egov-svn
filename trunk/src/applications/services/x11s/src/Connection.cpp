// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#include "Connection.h"

Connection::Connection(QTcpSocket *socket)
 : QObject(0), m_socket(socket)
{
  if (! m_socket) {
    qDebug() << "no socket";
    return;
  }

  connect(m_socket, SIGNAL(disconnected()),
          m_socket, SLOT(deleteLater()));
  connect(m_socket, SIGNAL(readyRead()),
          this,     SLOT(onReadyRead()));
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

  QByteArray data = m_socket->readAll();

  m_socket->write(data);
  qDebug() << data;

  //m_socket->write(data);
  //m_socket->disconnectFromHost();
}

