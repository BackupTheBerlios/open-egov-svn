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

#include <OEG/Qt/ToolProvider.h>

#include <QAction>
#include <QApplication>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include "Thread.h"

Thread::Thread(QObject *parent /*=0*/)
 : QThread(parent)
{
}

Thread::~Thread()
{
}

void Thread::run()
{
  qDebug() << "Worker thread:" << thread()->currentThreadId();

  connect(this, SIGNAL(finished()),                                  // The the GUI thread that we are finished and
          this, SLOT(sendThreadFinished()), Qt::DirectConnection);   // give a pointer to the thread.

  QNetworkAccessManager *manager = new QNetworkAccessManager();
  connect(manager, SIGNAL(finished(QNetworkReply *)),
          this,    SLOT(replyFinished(QNetworkReply *)));

  QNetworkRequest request;
  request.setUrl(QUrl("http://www.heise.de/"));
  request.setRawHeader("User-Agent", "Open eGovernment Browser 1.0");

  QNetworkReply *reply = manager->get(request);

  connect(reply, SIGNAL(readyRead()),
          this,  SLOT(slotReadyRead()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
          this,  SLOT(slotError(QNetworkReply::NetworkError)));
  connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
          this,  SLOT(slotSslErrors(QList<QSslError>)));

  exec();
}

void Thread::replyFinished(QNetworkReply *reply)
{
  qDebug() << "Thread::replyFinished()";

  reply->deleteLater();
}

void Thread::setPath(const QUrl &path)
{
  m_path = path;
}

void Thread::sendThreadFinished()
{
  emit threadFinished(this);
}

