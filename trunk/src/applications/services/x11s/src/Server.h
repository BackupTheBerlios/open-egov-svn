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

#pragma once

#include <QObject>
#include <QString>
#include <QHostAddress>

#include "Atoms.h"

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

    static qint16   m_protocol_major_version;
    static qint16   m_protocol_minor_version;
    static QString  m_vendor;
    static int      m_release_number;

    bool start();
    void reset();
    void close();

  protected:

  signals:
    void clientCountChanged();

  private slots:
    void newConnection();
    void deleteConnection(Connection *conn);

  protected:
    QTcpServer          *m_server;
    QList<Connection *>  m_connections;
    QHostAddress         m_host_adress;
    Atoms                m_atoms;

    QString              m_ip_address;         // The IP address the server uses.
    unsigned int         m_server_number;      // 0 .. x, maps to port number 6000 .. 6000+x.
    bool                 m_auto_exit_x11s;     // If the last window closes X11S exists.
    unsigned int         m_auto_exit_time;     // After closing last window the server waits X seconds.
    bool                 m_disable_bell;       // Be nice.
    bool                 m_access_control;     // Enable access control.
};

