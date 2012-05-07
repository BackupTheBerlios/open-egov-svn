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
#include <QCloseEvent>
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

#include "ColorMap.h"
#include "Connection.h"
#include "Font.h"
#include "Format.h"
#include "Server.h"
#include "Mouse.h"
#include "Screen.h"

qint16   Server::m_protocol_major_version = 11;
qint16   Server::m_protocol_minor_version = 0;
QString  Server::m_vendor                 = "open-egov.de X11 Server";
int      Server::m_release_number         = 0;

Server::Server(QObject *parent/*=0*/)
 : QObject(parent)
{
  m_grab_server     = 0;
  m_ip_address      = "192.168.178.23";
  m_server_number   = 0;
  m_auto_exit_x11s  = true;
  m_auto_exit_time  = 3600;  // 1 hour.
  m_disable_bell    = true;
  m_access_control  = true;

  m_access_control_enabled = false;
  m_access_control_allowed_hosts.clear();

  m_client_id_bits = 20;
  m_client_id_step = (1 << m_client_id_bits);
  m_client_id_base = m_client_id_step;

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

  m_formats.append(new Format(32, 24, 8));
}

Server::~Server()
{
  qDebug() << "Server::~Server()";

  close();

  qDebug() << "  end";
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

int Server::numberOfPixmapFormats() const
{
  return m_formats.size();
}

// The X11 server's keyboard.

Keyboard *Server::keyboard() const
{
  return m_keyboard;
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

// Resets the X11 server after the last client
// disconnects with close-down mode "destroy".

void Server::reset()
{
  m_atoms.reset();
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
  qDebug() << "XServer::newConnection(): New connection.";

  Connection *connection = new Connection(m_server->nextPendingConnection(), this);
  if (connection) {
    connection->setResourceIdBase(m_client_id_base);
    connection->setResourceIdMask(m_client_id_step - 1);
    m_client_id_base += m_client_id_step;
 
    connection->init();

    connect(connection, SIGNAL(disconnected(Connection *)),
            this,       SLOT(deleteConnection(Connection *)));

    m_connections.append(connection);

    emit clientCountChanged();
  }
}

void Server::deleteConnection(Connection *connection)
{
  qDebug() << "XServer::deleteConnection(): Deleting connection.";

  if (! connection)
    return;

  for (int i=0; i<m_connections.size(); i++) {
qDebug() << "1";
    if (m_connections.at(i) == connection) {
      delete m_connections.takeAt(i);   // TODO: Send close signal and wait with timeout.
qDebug() << "2";
      emit clientCountChanged();
    }
  }
qDebug() << "3";
}

// Write details of all the pixmap formats.

void Server::writeFormats(Connection *connection)
{
  foreach(Format *format, m_formats)
    format->write(connection);
}

// This client grabs the server for itself.
// All other clients are disabled now.

void Server::grabServer(Connection *connection)
{
  m_grab_server = connection;
}

// End the server grab.

void Server::ungrabServer(Connection *connection)
{
  if (m_grab_server == connection)
    m_grab_server = 0;
}

// Processing is allowed, if no other client has grabbed
// the server exclusively.

bool Server::processingAllowed(Connection *connection)
{
  if (! m_grab_server)
    return true;

  if (m_grab_server == connection)
    return true;

  return false;
}

// Sets access control flag. "false" means no access control,
// then all hosts are allowed to connect.

void Server::setAccessControl(bool enabled)
{
  m_access_control_enabled = enabled;
}

// Determines, if a client coming from an IP address is
// allowed to connect to the server.

bool Server::accessAllowed(int address) const
{
  if (! m_access_control_enabled)                          // No access control active.
    return true;                                           // All clients are allowed to connect.

  return m_access_control_allowed_hosts.contains(address);
}

