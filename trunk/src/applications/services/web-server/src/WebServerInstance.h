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

#pragma once

#include <OEG/Common.h>

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QTimer>

#include "RequestData.h"

class WebServer;

class WebServerInstance : public QObject
{
  Q_OBJECT

  public:
    WebServerInstance(int socketDescriptor, WebServer *server);

    void run();
    void handleRequest();

  protected slots:
    void closeConnection();

  protected:
    void parseRequest();

  private slots:
    void readPartialRequest();
    void sendResponse();
    void errorMessage(QAbstractSocket::SocketError socketError);

  signals:
    void error(QTcpSocket::SocketError socketError);
    void readRequestFinished();

  private:
    int          m_socket_descriptor;
    WebServer   *m_server;
    QTcpSocket  *m_socket;
    QByteArray   m_array;
    RequestData  m_request;
    bool         m_request_finished;
    QTimer      *m_disconnect_timer;
};

