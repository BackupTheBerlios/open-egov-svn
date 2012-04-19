// $Id$
//
// Open eGovernment
// Copyright (C) 2004-2012 by Gerrit M. Albrecht
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

#include <OEG/Qt/Application.h>

#include <QAction>
#include <QApplication>
#include <QByteArray>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

#include "Connection.h"
#include "X11defines.h"
#include "Server.h"

qint16   Server::m_protocol_major_version = 11;
qint16   Server::m_protocol_minor_version = 0;
QString  Server::m_vendor                 = "open-egov.de X11 Server";
int      Server::m_release_number         = 0;

Server::Server(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_ip_address      = "";
  m_server_number   = 0;
  m_auto_exit_x11s  = true;
  m_auto_exit_time  = 3600;  // 1 hour.
  m_disable_bell    = true;
  m_access_control  = true;

  if (m_ip_address.isEmpty()) {
    m_host_adress = QHostAddress(QHostAddress::LocalHost);
    m_ip_address  = "local"; // host_adress.toString();
  }
  else if (m_ip_address == "any") {
    m_host_adress = QHostAddress(QHostAddress::Any);
  }
  else if (m_ip_address == "local") {
    m_host_adress = QHostAddress(QHostAddress::LocalHost);
  }
  else {
    m_host_adress.setAddress(m_ip_address);
  }
}

Server::~Server()
{
  close();
}

QString Server::errorString() const
{
  return m_server->errorString();
}

unsigned int Server::serverPort() const
{
  return 6000 + m_server_number;
}

QHostAddress Server::serverAddress() const
{
  return m_server->serverAddress();
}

bool Server::start()
{
  m_server = new QTcpServer(this);
  if (! m_server->listen(m_host_adress, serverPort())) {
    return false;
  }

  qDebug() << "Host:" << serverAddress().toString() << "Port:" << serverPort();

  connect(m_server, SIGNAL(newConnection()),
          this,     SLOT(newConnection()));

  return true;
}

void Server::reset()
{
}

void Server::close()
{
  while (! m_connections.isEmpty()) {
    Connection *connection = m_connections.takeFirst();
    if (connection) {
      delete connection;
      emit clientCountChanged();
    }
  }

  if (m_server) {
    m_server->close();
    delete m_server; m_server = 0;
  }
}

unsigned int Server::clientCount() const
{
  return m_connections.count();
}

void Server::newConnection()
{
  qDebug() << "XServer::newConnection(): New connection.";

  Connection *conn = new Connection(m_server->nextPendingConnection());
  if (conn) {
    connect(conn, SIGNAL(disconnected(Connection *)),
            this, SLOT(deleteConnection(Connection *)));

    m_connections.append(conn);

    emit clientCountChanged();
  }
}

void Server::deleteConnection(Connection *conn)
{
  qDebug() << "XServer::deleteConnection(): Deleting connection.";

  if (! conn)
    return;

  for (int i=0; i<m_connections.size(); i++) {
    if (m_connections.at(i) == conn) {
      delete m_connections.takeAt(i);

      emit clientCountChanged();
    }
  }
}

