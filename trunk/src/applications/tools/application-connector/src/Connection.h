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

#include <OEG/Common.h>

#include <QByteArray>
#include <QString>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QObject>

class QTcpSocket;
class Server;

class Connection : public QObject
{
  Q_OBJECT

  public:
    Connection(QTcpSocket *socket, Server *server);
    virtual ~Connection();

    void    init();
    bool    isValid();
    void    flush();

  signals:
    void disconnected(Connection *);

  private slots:
    void onReadyRead();
    void emitDisconnected();

  private:
    bool                    m_close_connection;            // True if client is killed or server shuts down.
    QTcpSocket             *m_socket;
    Server                 *m_server;
};

