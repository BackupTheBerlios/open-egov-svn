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

#include <QApplication>
#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QList>
#include <QLatin1String>
#include <QMessageBox>
#include <QTcpSocket>

#include <OEG/OpenStreetMap/Client.h>
#include <OEG/OpenStreetMap/Element.h>

using namespace OEG::OpenStreetMap;
using namespace Qt;

Client::Client(QObject *parent)
 : QObject(parent)
{
  m_socket = new QTcpSocket(this);

  connect(m_socket, SIGNAL(readyRead()),
          this,     SLOT(readResponse()));
  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
          this,     SLOT(networkError(QAbstractSocket::SocketError)));

  connectOSM();
}

Client::~Client()
{
  disconnectOSM();

  if (m_socket) {
    delete m_socket; m_socket = 0;
  }
}

void Client::connectOSM()
{
  if (m_socket) {
    m_socket->connectToHost("api06.dev.openstreetmap.org", 80);
    if (! m_socket->waitForConnected(1000))
      qDebug() << "not connected...";
  }
}

void Client::disconnectOSM()
{
  if (m_socket) {
    m_socket->disconnectFromHost();
    m_socket->close();
    m_socket->abort();
  }
}

void Client::ensureConnectionOSM()
{
  if (! m_socket)
    qDebug() << "no socket";

  if (m_socket->state() != QAbstractSocket::ConnectedState)
    qDebug() << "socket has not a connected state";
}

// http://wiki.openstreetmap.org/wiki/API_v0.6#Changesets

void Client::createChangeset()
{
  ensureConnectionOSM();

  QString s = "";

  m_socket->write(s.toLatin1());
}

// GET /api/0.6/changeset/id

void Client::closeChangeset()
{
  ensureConnectionOSM();

}

void Client::updateChangeset()
{
  ensureConnectionOSM();

}

void Client::readChangeset()
{
  ensureConnectionOSM();

}

// http://wiki.openstreetmap.org/wiki/API_v0.6#Changesets

void Client::createElement(Element *element)
{
  if (! element)
    return;

  QString xml = element->toXML();

}

void Client::readElement(Element *element)
{
  if (! element)
    return;

  QString xml = element->toXML();

}

void Client::updateElement(Element *element)
{
  if (! element)
    return;

  QString xml = element->toXML();

}

void Client::deleteElement(Element *element)
{
  if (! element)
    return;

  QString xml = element->toXML();

}

void Client::readResponse()
{
  QByteArray ba;
  int numBytes;

  while ((numBytes = m_socket->bytesAvailable()) > 0) {
    ba = m_socket->readLine(numBytes);
    qDebug() << ba;
  }
}

void Client::networkError(QAbstractSocket::SocketError socketError)
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
                                 "Make sure the fortune server is running, "
                                 "and check that the host name and port "
                                 "settings are correct."));
      break;
    default:
      QMessageBox::information(0, qApp->applicationName(),
                               QString(_("The following error occurred: %1.")).arg(m_socket->errorString()));
  }
}

QString Client::generator()
{
  return "Open eGovernment GIS component";
}

