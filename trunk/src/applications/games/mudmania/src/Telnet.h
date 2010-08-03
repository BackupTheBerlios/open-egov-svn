// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

class QTcpSocket;

class Telnet : public QObject
{
  Q_OBJECT

  // This enum specifies control messages you can send to the Telnet server using sendControl().

  enum Control {
    GoAhead,            // Sends the GO AHEAD control message, meaning that the server can continue to send data.
    InterruptProcess,   // Interrupts the current running process on the server. This is the equivalent of pressing Ctrl+C in most terminal emulators.
    AreYouThere,        // Sends the ARE YOU THERE control message, to check if the connection is still alive.
    AbortOutput,        // Temporarily suspends the output from the server. The output will resume if you send this control message again.
    EraseCharacter,     // Erases the last entered character.
    EraseLine,          // Erases the last line.
    Break,              // Sends the BREAK control message.
    EndOfFile,          // Sends the END OF FILE control message.
    Suspend,            // Suspends the current running process on the server. Equivalent to pressing Ctrl+Z in most terminal emulators.
    Abort               // Sends the ABORT control message.
  };

  enum Command {
    IAC   = 255,        // Interpret as command.
    DONT  = 254,        // Stop performing.
    DO    = 253,        // Perform.
    WONT  = 252,        // Refusal to perform.
    WILL  = 251,        // Desire to begin performing.
    SB    = 250,        // Subnegotiation of the indicated option follows.
    GA    = 249,        // Go ahead.
    EL    = 248,        // Erase line.
    EC    = 247,        // Erase character.
    AYT   = 246,        // Are you there.
    AO    = 245,        // Abort output.
    IP    = 244,        // Suspend, interrupt or abort the process.
    BRK   = 243,        // Break.
    DM    = 242,        // Data mark. Indicates the position of a Synch event within the data stream.
    NOP   = 241,        // No operation.
    SE    = 240         // End of subnegotiation parameters.
  };

  public:
    Telnet(QObject *parent, const char *name);
    virtual ~Telnet();

    void connectToHost(const QString &host = "", quint16 port = 23);
    void loginUser(const QString &username = "", const QString &password = "");

    QTcpSocket *socket() const;
    void setSocket(QTcpSocket *socket);

    bool isConnected() const;
    QString terminalType() const;

  public slots:
    void sendControl(Control ctrl);
    void sendData(const QString &data);
    void sendSync();

    void readFromSocket();
    void connected();
    void connectionClosed();

    void close();
    void logout();

  signals:
    void message(const QString &data);
    void loginRequired();
    void loginFailed();
    void loggedOut();
    void loggedIn();
    void connectionError(int error);

  protected:
    QTcpSocket   *m_socket;
    bool          m_echo_on;
    bool          m_logged_in;
    bool          m_connected;
    QString       m_host;
    unsigned int  m_port;
    QString       m_username;
    QString       m_password;
    QObject      *m_parent;
};

