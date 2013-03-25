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

#include <QCoreApplication>
#include <QStringList>
#include <QTime>
#include <QObject>
#include <QHostAddress>

#include <stdlib.h>
#include <process.h>

#include "WebServer.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  app.setApplicationName("WebServer");
  app.setApplicationVersion("0.03");
  app.setOrganizationName("Open E-Government Project");
  app.setOrganizationDomain("open-egov.de");

  if (QCoreApplication::arguments().contains("--verbose")) {
    qDebug() << app.applicationName() << " Version " << app.applicationVersion();
    qDebug() << "Running with PID: " << getpid();
  }

  //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

  WebServer server;
  //http://doc.trolltech.com/4.5/qhostaddress.html
  //Null, LocalHost, LocalHostIPv6, Broadcast, and Any.
  //QHostAddress::AnyIPv6
  //QHostAddress::LocalHostIPv6
  if (! server.listen(QHostAddress::Any, 80)) {
    qDebug() << "Unable to start the server: " << server.errorString();
    return 0;
  }

  qDebug() << QObject::tr("The server is running on port %1.").arg(server.serverPort());

  return app.exec();
}

