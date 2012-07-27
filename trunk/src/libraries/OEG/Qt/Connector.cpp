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

#include <OEG/Qt/Connector.h>
#include <OEG/Qt/ConnectorMessage.h>

#include <QHostAddress>
#include <QTcpSocket>
#include <QTextCodec>
#include <QTextStream>

using namespace OEG::Qt;
using namespace Qt;

Connector::Connector(QObject *parent /*=0*/)
 : QObject(parent)
{
  qDebug() << "Connector";

  m_socket = new QTcpSocket(this);

  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
          this,     SLOT(onError(QAbstractSocket::SocketError)));
  connect(m_socket, SIGNAL(connected()),
          this,     SLOT(onConnected()));
  connect(m_socket, SIGNAL(readyRead()),
          this,     SLOT(onReadyRead()));
  connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
          this,     SLOT(onStateChanged(QAbstractSocket::SocketState)));
  connect(m_socket, SIGNAL(hostFound()),
          this,     SLOT(onHostFound()));
  connect(m_socket, SIGNAL(disconnected()),
          this,     SLOT(onDisconnected()));
}

Connector::~Connector()
{
  qDebug() << "~Connector";

  disconnectFromServer();                                  // Calls disconnectFromHost();

  if (m_socket) {
    disconnect(m_socket, 0, 0, 0);

    delete m_socket;
    m_socket = 0;
  }
}

void Connector::connectToServer()
{
  qDebug() << "Connector::connectToServer()";

  // QHostAddress::LocalHost
  //m_socket->connectToHost("127.0.0.1", 7000);              // http://qt-project.org/doc/qt-4.8/qhostaddress.html
  //if (m_socket->waitForConnected(1000))
  //  qDebug("Connected!");

  // TODO: handle timeout, don't send data into a missing connection...
  // if (! socketConnected()) ...

  // TODO: Restart application-connector.exe if process is not running...
}

void Connector::onConnected()
{
  qDebug() << "Connector::onConnected()";
  send("application-connector", "hana");
}

void Connector::disconnectFromServer()
{
  qDebug() << "Connector::disconnectFromServer()";

  if (! m_socket)
    return;

  m_socket->disconnectFromHost();

  if (m_socket->state() == QAbstractSocket::UnconnectedState)
    return;

  if (! m_socket->waitForDisconnected(1000))
    m_socket->close();
}

void Connector::send(const QString &to, const QString &text)
{
  ConnectorMessage *message = createMessage();

  message->m_to   = to;
  message->m_text = text;
  message->m_from = "app-id session-id window-id ";

  send(message);
}

void Connector::send(ConnectorMessage *message)
{
  if (! message) {
    qDebug() << "Connector::send(): No message.";
    return;
  }

  if (! socketConnected()) {
    qDebug() << "Connector::send(): Not connected.";
    return;
  }

  QTextCodec *codec = QTextCodec::codecForName("UTF_8");
  QTextCodec::setCodecForCStrings(codec);

  QTextStream out(m_socket);

  out << message->toString();

  delete message;
}

void Connector::onReadyRead()
{
  if (! m_socket->canReadLine()) {
    qDebug() << "Connector::onReadyRead(): No data.";
    return;
  }

  if (! socketConnected()) {
    qDebug() << "Connector::onReadyRead(): Not connected.";
    return;
  }

  QString s = m_socket->readLine();

  qDebug() << "read:" << s;

  handleMessage(createMessage(s));
}

void Connector::onStateChanged(QAbstractSocket::SocketState state)
{
  qDebug() << "Connector::onStateChanged()";

  switch (state) {
    case QAbstractSocket::UnconnectedState:
      qDebug() << "UnconnectedState: The socket is not connected.";
      break;
    case QAbstractSocket::HostLookupState:
      qDebug() << "HostLookupState: The socket is performing a host name lookup.";
      break;
    case QAbstractSocket::ConnectingState:
      qDebug() << "ConnectingState: The socket has started establishing a connection.";
      break;
    case QAbstractSocket::ConnectedState:
      qDebug() << "ConnectedState: A connection is established.";
      break;
    case QAbstractSocket::BoundState:
      qDebug() << "BoundState: The socket is bound to an address and port (for servers).";
      break;
    case QAbstractSocket::ClosingState:
      qDebug() << "ClosingState: The socket is about to close (data may still be waiting to be written).";
      break;
    case QAbstractSocket::ListeningState:
      qDebug() << "ListeningState: For internal use only.";
      break;
  }
}

void Connector::onError(QAbstractSocket::SocketError error)
{
  qDebug() << "Connector::onError()";

  switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
      qDebug() << "The connection was refused by the peer (or timed out).";
      break;
    case QAbstractSocket::RemoteHostClosedError:
      qDebug() << "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
      break;
    case QAbstractSocket::HostNotFoundError:
      qDebug() << "The host address was not found.";
      break;
    case QAbstractSocket::SocketAccessError:
      qDebug() << "The socket operation failed because the application lacked the required privileges.";
      break;
    case QAbstractSocket::SocketResourceError:
      qDebug() << "The local system ran out of resources (e.g., too many sockets).";
      break;
    case QAbstractSocket::SocketTimeoutError:
      qDebug() << "The socket operation timed out.";
      break;
    case QAbstractSocket::DatagramTooLargeError:
      qDebug() << "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
      break;
    case QAbstractSocket::NetworkError:
      qDebug() << "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
      break;
    case QAbstractSocket::AddressInUseError:
      qDebug() << "The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.";
      break;
    case QAbstractSocket::SocketAddressNotAvailableError:
      qDebug() << "The address specified to QUdpSocket::bind() does not belong to the host.";
      break;
    case QAbstractSocket::UnsupportedSocketOperationError:
      qDebug() << "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
      break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
      qDebug() << "The socket is using a proxy, and the proxy requires authentication.";
      break;
    case QAbstractSocket::SslHandshakeFailedError:
      qDebug() << "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket).";
      break;
    case QAbstractSocket::UnfinishedSocketOperationError:
      qDebug() << "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
      break;
    case QAbstractSocket::ProxyConnectionRefusedError:
      qDebug() << "Could not contact the proxy server because the connection to that server was denied.";
      break;
    case QAbstractSocket::ProxyConnectionClosedError:
      qDebug() << "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established).";
      break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
      qDebug() << "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
      break;
    case QAbstractSocket::ProxyNotFoundError:
      qDebug() << "The proxy address set with setProxy() (or the application proxy) was not found.";
      break;
    case QAbstractSocket::ProxyProtocolError:
      qDebug() << "The connection negotiation with the proxy server because the response from the proxy server could not be understood.";
      break;
    case QAbstractSocket::UnknownSocketError:
      qDebug() << "An unidentified error occurred.";
      break;
  }

  m_socket->close();
}

void Connector::onHostFound()
{
  qDebug() << "Connector::onHostFound()";
}

void Connector::handleMessage(ConnectorMessage *message)
{
  if (! message) {
    qDebug() << "Connector::handleMessage(): No message.";
    return;
  }


  delete message;
}

void Connector::onDisconnected()
{
  qDebug() << "Connector::onDisconnected()";
}

bool Connector::socketConnected()
{
  if (! m_socket->isValid())
    return false;

  if (m_socket->state() == QAbstractSocket::ConnectedState)
    return true;

  return false;
}

ConnectorMessage *Connector::createMessage(const QString &s /*=""*/)
{
  ConnectorMessage *message = new ConnectorMessage(this);

  if (! message) {
    qDebug() << "Connector::createMessage(): No message.";
    return 0;
  }

  if (s.length() > 0) {                                    // Parse string and extract message.

  }

  return message;
}

