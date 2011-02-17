// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <QAbstractSocket>
#include <QString>
#include <QThread>

class ViewPlayer;
class Telnet;

class ConnectionThread : public QThread
{
  Q_OBJECT

  public:
    ConnectionThread(ViewPlayer *parent);

    void run();

  signals:
    void startedEventLoop();

  public slots:
    bool connectHost(const QString &host = "", unsigned int port = 23);
    void loginUser(const QString &username = "", const QString &password = "");
    void disconnectHost();

    void displayError(QAbstractSocket::SocketError socketError);

    void gotFinished();
    void gotStarted();
    void gotTerminated();                       

  protected:
    Telnet     *m_telnet;
    ViewPlayer *m_parent;
};

