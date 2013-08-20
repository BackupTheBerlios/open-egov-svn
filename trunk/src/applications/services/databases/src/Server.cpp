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

#include <OEG/Qt/Application.h>

#include <QObject>
#include <QApplication>
#include <QAction>
#include <QIcon>
#include <QStringList>
#include <QByteArray>
#include <QCloseEvent>
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

#include "Connection.h"
#include "Server.h"

Server::Server(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_ip_address      = ""; //"192.168.178.23";

  if (m_ip_address.isEmpty()) {
    m_host_adress = QHostAddress(QHostAddress::LocalHost);
    m_ip_address  = "local"; // host_adress.toString();
  }
  else if (m_ip_address == "any") {
    m_host_adress = QHostAddress(QHostAddress::Any);
  }
  else if (m_ip_address == "localhost") {
    m_host_adress = QHostAddress(QHostAddress::LocalHost);
  }
  else {
    m_host_adress.setAddress(m_ip_address);
  }
}

Server::~Server()
{
  qDebug() << "Server::~Server()";

  close();

  qDebug() << "Server::~Server(): end";
}

QString Server::errorString() const
{
  return m_server->errorString();
}

unsigned int Server::serverPort() const
{
  return 7001;
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

// Terminate all connected clients and
// stop listening on the tcp socket.

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
  qDebug() << "Server::newConnection(): New connection.";

  Connection *connection = new Connection(m_server->nextPendingConnection(), this);
  if (! connection) {
    qDebug() << "Server::newConnection(): No connection.";
    return;
  }

  connection->init();

  connect(connection, SIGNAL(disconnected(Connection *)),
          this,       SLOT(deleteConnection(Connection *)));

  m_connections.append(connection);

  emit clientCountChanged();
}

void Server::deleteConnection(Connection *connection)
{
  qDebug() << "Server::deleteConnection(): Deleting connection.";

  if (! connection)
    return;

  for (int i=0; i<m_connections.size(); i++) {
    if (m_connections.at(i) == connection) {
      delete m_connections.takeAt(i);   // TODO: Send close signal and wait with timeout.
      qDebug() << "Server::deleteConnection(): Deleted connection.";
      emit clientCountChanged();
    }
  }
}

