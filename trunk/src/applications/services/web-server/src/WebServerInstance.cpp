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

#include <OEG/Common.h>

#include <QtNetwork>

#include "WebServer.h"
#include "WebPage.h"
#include "ResponseData.h"
#include "WebServerInstance.h"

WebServerInstance::WebServerInstance(int socketDescriptor, WebServer *server)
 : QObject(0), m_socket_descriptor(socketDescriptor), m_server(server), m_socket(0)
{
  m_disconnect_timer = new QTimer(this);

  connect(m_disconnect_timer, SIGNAL(timeout()), this, SLOT(closeConnection()));
}

void WebServerInstance::run()
{
  qDebug() << "WebServerInstance::run()";

  m_socket = new QTcpSocket();

  if (! m_socket->setSocketDescriptor(m_socket_descriptor)) {
    emit error(m_socket->error());
    return;
  }

  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
          this,     SLOT(errorMessage(QAbstractSocket::SocketError)));
//  connect(this,     SIGNAL(readRequestFinished()),         // We send response and data automatically.
//          this,     SLOT(sendResponse()));

  do {
    m_disconnect_timer->stop();

    connect(m_socket, SIGNAL(readyRead()),
            this,     SLOT(readPartialRequest()));
    handleRequest();

    if (! m_request_finished) {
      closeConnection();
      break;
	}

    if (m_request.connection() == "close") {
      closeConnection();
      break;
    }

    int i;
    if (m_request.connection() == "keep-alive") {
      i = m_request.keepAlive();

      if (i > 3600)                                        // 1 hour.
        i = 300;                                           // 5 minutes.
	}
	else {
      i = 300;
    }

 //   m_disconnect_timer->start(i * 1000);
 //   qDebug() << "waiting for next request on this connection. disconnect in " << i << " seconds.";
    //m_disconnect_timer->stop();

    if (m_request_finished) {
      disconnect(m_socket, SIGNAL(readyRead()), 0, 0);
      //emit readRequestFinished();                        // Send response.
	  sendResponse();
	}

    if (! m_socket)                                        // to be sure.
      break;
  } while (true);

  qDebug() << "Thread ends here.";

  if (m_disconnect_timer) {
    delete m_disconnect_timer; m_disconnect_timer = 0;
  }
}

void WebServerInstance::handleRequest()
{
  m_request_finished = false;

  qDebug() << "WebServerInstance::handleRequest()";

  if (! m_socket) {
    qDebug() << "no socket";
	return;
  }

  if (m_socket->state() == QAbstractSocket::UnconnectedState) {
    qDebug() << "no connection";
	return;
  }

  m_array.clear();                                         // Read buffer for request.
  m_request.clear();                                       // Parsed request lines.

//  connect(m_socket, SIGNAL(readyRead()),
//          this,     SLOT(readPartialRequest()));

  while (! m_request_finished) {                           // Else reading aborts to early.
    bool rc = m_socket->waitForReadyRead(10000);           // 10s.
	//if (! rc) {
    //  qDebug("Error while waiting for ready read...");
	//}
  }
}

void WebServerInstance::readPartialRequest()
{
  if (! m_socket)                                          // to be sure.
    return;

  //while ((m_socket->isReadable()) && (m_socket->bytesAvailable() > 0)) {
  while (m_socket->canReadLine()) {
    QByteArray neu = m_socket->readAll();
    neu.replace('\r', "");                                 // we don't need them
    m_array.append(neu);

    parseRequest();
  }
}

void WebServerInstance::parseRequest()
{
  int i;
  QString s;

  if (m_request_finished)
    return;

  while (true) {
    if (m_array.length() <= 0)                             // Nothing to parse.
      break;

    i = m_array.indexOf("\n");                             // In fact it is \r\n.

    if (i == -1) {                                         // No newline. End of array reached. Need to load more.
      qDebug("end of array. no newline.");
      // timeout?
      break;
    }

    if (i >= 0) {                                          // Newline found. Extract line. Then next loop.
      QByteArray line = m_array.left(i);
      s = line.data();
      s = s.trimmed();                                     // Are there side-effects with some request lines?
      m_array.remove(0, line.size() + 1);
      if (s.length() > 0) {
        m_request.addLine(s);
      } else {                                             // Empty line found. End of request reached. Stop.
        qDebug("end of request.");
        m_request_finished = true;
//        disconnect(m_socket, SIGNAL(readyRead()), 0, 0);
//        emit readRequestFinished();                        // Send response.
        break;
      }
    }
  }
}

void WebServerInstance::errorMessage(QAbstractSocket::SocketError socketError)
{
  QString error;

  m_request_finished = true;                               // Kills the waiting for new data loop.

  switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
      error = tr("The remote host closed the connection.");
      break;
    case QAbstractSocket::HostNotFoundError:
      error = tr("The host was not found. Please check the host name and port settings.");
      break;
    case QAbstractSocket::ConnectionRefusedError:
      error = tr("The connection was refused by the peer. "
                 "Make sure the server is running, "
                 "and check that the host name and port "
                 "settings are correct.");
      break;
    default:
      error = tr("The following error occurred: %1.").arg(m_socket->errorString());
  }

  qDebug() << "Error" << ": " << error;
}

void WebServerInstance::sendResponse()
{
  WebPage page;
  ResponseData response;

  page.setTitle("Das ist ein Titel");
  page.setContents("<h1>test</h1><p>test test test</p>");
  page.build();

  response.setContentType("text/html");
  response.setContentLength(page.length());

  //QByteArray array;
  //array.append(text);
  //m_socket->write(array);

  m_socket->write(response.data().toLatin1());
  m_socket->write("\r\n"); // OK?
  m_socket->write(page.source().toLatin1());
  m_socket->waitForBytesWritten();
  m_socket->flush();
}

// Called if reading the request timeouts or the requested timeout value
// for keeping the connection was reached. In both cases the connection
// will be closed silently.

void WebServerInstance::closeConnection()
{
  qDebug() << "WebServerInstance::closeConnection()";

  if (m_socket) {
    m_socket->disconnectFromHost();
    //m_socket->waitForDisconnected();
    m_socket->close();

    delete m_socket; m_socket = 0;
  }
}

