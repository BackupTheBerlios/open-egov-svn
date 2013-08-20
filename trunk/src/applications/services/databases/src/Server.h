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

#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QHostAddress>

class QAction;
class QIcon;
class QMenu;
class QTcpServer;

class Connection;

class Server : public QObject
{
  Q_OBJECT

  public:
    Server(QObject *parent = 0);
    virtual ~Server();

    QString errorString() const;
    unsigned int clientCount() const;
    unsigned int serverPort() const;
    QHostAddress serverAddress() const;

    bool start();
    void close();

  signals:
    void clientCountChanged();

  private slots:
    void newConnection();
    void deleteConnection(Connection *connection);

  protected:
    QTcpServer          *m_server;
    QList<Connection *>  m_connections;
    QHostAddress         m_host_adress;
    QString              m_ip_address;         // The IP address the server uses.
};

