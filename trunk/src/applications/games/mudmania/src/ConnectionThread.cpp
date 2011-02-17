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

#include <QApplication>
#include <QMessageBox>
#include <QTcpSocket>
#include <QThread>
#include <QDebug>

#include "ConnectionThread.h"
#include "MainWindow.h"
#include "Telnet.h"
#include "ViewPlayer.h"

ConnectionThread::ConnectionThread(ViewPlayer *parent)
 : m_parent(parent)
{
}

void ConnectionThread::gotFinished()
{
  qWarning() << "got finished";
}

void ConnectionThread::gotStarted()
{
  qWarning() << "got started";
}

void ConnectionThread::gotTerminated()
{
  qWarning() << "got terminated";
}

// Geht das in einem nicht-GUI-Thread überhaupt noch?

void ConnectionThread::displayError(QAbstractSocket::SocketError socketError)
{
  switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
      break;
    case QAbstractSocket::HostNotFoundError:
      QMessageBox::information(0, qApp->applicationName(),
                               _("The host was not found. Please check the "
                                 "host name and port settings."));
      break;
    case QAbstractSocket::ConnectionRefusedError:
      QMessageBox::information(0, qApp->applicationName(),
                               _("The connection was refused by the peer. "
                                 "Make sure the telnet server is running, "
                                 "and check that the host name and port "
                                 "settings are correct."));
      break;
    default:
      QMessageBox::information(0, qApp->applicationName(),
                               QString(_("The following error occurred: %1."))
                                       .arg(m_telnet->socket()->errorString()));
  }
}

void ConnectionThread::run()
{
  qWarning() << "ConnectionThread::run()";
  qWarning() << "  parent = " << ((m_parent == 0) ? 0 : 1);

  m_telnet = new Telnet(this, "telnet");

  connect(m_telnet, SIGNAL(message(const QString &)),
          m_parent, SLOT(receiveText(const QString &)));
  connect(m_parent, SIGNAL(sendText(const QString &)),
          m_telnet, SLOT(sendData(const QString &)));

  connect(this, SIGNAL(finished()),   this, SLOT(gotFinished()));
  connect(this, SIGNAL(started()),    this, SLOT(gotStarted()));
  connect(this, SIGNAL(terminated()), this, SLOT(gotTerminated()));

  emit startedEventLoop();

  exec();
}

bool ConnectionThread::connectHost(const QString &host /*=""*/, unsigned int port /*=23*/)
{
  qWarning() << "ConnectionThread::connectHost() fini = " << isFinished() << "  running = " << isRunning();

  m_telnet->close();
  m_telnet->connectToHost(host, port);

  if (m_telnet->socket()->waitForConnected(3000)) {
    qDebug("Connected.");
    return true;
  }

  return false;
}

void ConnectionThread::loginUser(const QString &username /*=""*/, const QString &password /*=""*/)
{
  m_telnet->loginUser(username, password);
}

void ConnectionThread::disconnectHost()
{
  m_telnet->close();
}

