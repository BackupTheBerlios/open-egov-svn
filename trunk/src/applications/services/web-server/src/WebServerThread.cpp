// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <QtNetwork>

#include "WebServerThread.h"
#include "WebServerInstance.h"
#include "WebServer.h"

WebServerThread::WebServerThread(int socketDescriptor, WebServer *parent)
 : QThread(parent), m_socket_descriptor(socketDescriptor), m_server(parent)
{
  m_server->m_sessions_lock.lockForRead();   // Check sessions.
  //m_server->m_sessions
  m_server->m_sessions_lock.unlock();

}

void WebServerThread::run()
{
  qDebug() << "WebServerThread::run() BEGIN";

  WebServerInstance server(m_socket_descriptor, m_server);  // TODO

  server.run();

  qDebug() << "WebServerThread::run() END";
}

