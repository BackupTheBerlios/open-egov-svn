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

#include <QObject>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QAbstractSocket>
#include <QDebug>

class QTcpSocket;
class QUdpSocket;

namespace OEG { namespace Qt {

class ConnectorMessage;

class Connector : public QObject
{
  Q_OBJECT

  public:
    Connector(QObject *parent = 0);                        // Construct the socket and initialize me.
    ~Connector();                                          // Disconnect from the connector using close() and delete all.

    void connectToServer();                                // Connect to the application connector and greet it.
    void disconnectFromServer();                           // Disconnect from the connector.

    void send(const QString &to, const QString &text);
    void send(ConnectorMessage *message);

    void handleMessage(ConnectorMessage *message);

  public slots:
    void onConnected();                                    // Called after start() when the socket enters the connected state.
    void onReadyRead();                                    // Receive a message and store it into a ConnectorMessage object.
	void onError(QAbstractSocket::SocketError error);      // Error message in case an error occurs.
    void onStateChanged(QAbstractSocket::SocketState state); // For debugging purposes.
    void onHostFound();                                    // For debugging purposes.
    void onDisconnected();

  protected:
    bool socketConnected();
    ConnectorMessage *createMessage(const QString &s = "");

  private:
    QTcpSocket  *m_socket;
};

}}

