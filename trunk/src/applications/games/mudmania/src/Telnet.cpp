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

// http://doc.trolltech.com/solutions/4/qttelnet/qttelnet.html

#include <QDebug>
#include <QIODevice>
#include <QTcpSocket>

#include "Telnet.h"

Telnet::Telnet(QObject *parent, const char *name)
 : QObject(parent)
{
  setObjectName(name);

  if (! parent)
    qWarning() << "Telnet -> parent is 0";

  m_parent = parent;

  m_echo_on   = false;
  m_logged_in = false;
  m_connected = false;
  m_socket    = 0;

  m_host      = "";
  m_port      = 23;
  m_username  = "";
  m_password  = "";
}

Telnet::~Telnet()
{
  close();
}

bool Telnet::isConnected() const
{
 return m_connected;
}

void Telnet::connectToHost(const QString &host /*=""*/, quint16 port /*=23*/)
{
  close();

  m_socket = new QTcpSocket(this);

  if (! m_socket)
    return;

  connect(m_socket, SIGNAL(readyRead()),        this, SLOT(readFromSocket()));
  connect(m_socket, SIGNAL(connected()),        this, SLOT(connected()));
  connect(m_socket, SIGNAL(connectionClosed()), this, SLOT(connectionClosed()));

  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
          m_parent, SLOT(displayError(QAbstractSocket::SocketError)));

  if (host.length() > 0) {
    m_host = host;
    m_port = port;
  }

  m_socket->connectToHost(host, port, QIODevice::ReadWrite);

  if (m_socket->waitForConnected())
    m_connected = true;
}

void Telnet::loginUser(const QString &username, const QString &password)
{
  if (username.length() > 0)
    m_username = username;

  if (password.length() > 0)
    m_password = password;

  
}

void Telnet::sendControl(Control ctrl)
{
}

void Telnet::sendData(const QString &data)
{
  if (!m_connected || !m_socket)
    return;

  m_socket->write(data.toLatin1()); // correct charset?
  m_socket->flush();
}

void Telnet::sendSync()
{
}

QTcpSocket *Telnet::socket () const
{
  return m_socket;
}

void Telnet::setSocket(QTcpSocket *socket)
{
  if (m_logged_in) {
    logout();

    m_socket->flush();
  }

  if (m_socket) {
    //close();          // Is a timeout possible here?
    delete m_socket;
  }

  m_connected = false;

  m_socket = socket;  // TODO: connect the object here.
}

void Telnet::readFromSocket()
{
  if (m_socket->bytesAvailable() <= 0)
    return;

  //if (m_socket->canReadLine())

  QByteArray data = m_socket->readAll();

  // PARSE FOR TELNET NEGOTIATIONS

  while (true) {
    int pos = data.indexOf((char) 255);                    // Zero-based position of the IAC.

    if (pos < 0) {                                         // No IAC found.
      emit message(QString(data));

      break;
    }

    emit message(QString(data.left(pos)));                 // The text is okay, send it to the view.

    int len = data.length() - pos - 1;                     // Length of the right side of pos.

    if (len > 0) {
      emit message(QString("IAC "));

      data = data.right(len);

      QDataStream ds(&data, QIODevice::ReadOnly);
      quint8 cmd;

      if (! ds.atEnd()) {
        ds >> cmd; len--;

        switch (cmd) {
          case WILL: emit message(QString("WILL ")); break;
          case WONT: emit message(QString("WONT ")); break;
          case DO:   emit message(QString("DO "));   break;
          case DONT: emit message(QString("DONT ")); break;
          case SB:   emit message(QString("SB "));   break;
          case SE:   emit message(QString("SE "));   break;

          default:
            emit message(QString("<unknown command level 1: " + QString::number(cmd) + ">"));
            break;
        }
      }

      if (! ds.atEnd()) {
        ds >> cmd; len--;

        switch (cmd) {
          //case WILL: emit message(QString("WILL ")); break;

          default:
            emit message(QString("<unknown command level 2: " + QString::number(cmd) + ">"));
            break;
        }
      }
    }
  }
}

void Telnet::connected()
{
  m_connected = true;
}

void Telnet::connectionClosed()
{
  m_connected = false;
}

void Telnet::close()
{
  m_connected = false;

  if (m_logged_in) {
    logout();
  }

  if (m_socket) {
    m_socket->close();  // Or should we call disconnectFromHost()  instead?

    delete m_socket;

    m_socket = 0;

    //if (m_telnet->socket()->waitForDisconnected(1000))
    //  qDebug("Disconnected.");
  }

  emit loggedOut();
}

void Telnet::logout()
{
  if (!m_logged_in || !m_connected || !m_socket)
    return;




  m_socket->flush();

  close();
}

// Get the current terminal type for TTYPE telnet option.
// Returns: the string id of the terminal.

QString Telnet::terminalType() const
{
  return QString("mudmania");
}

