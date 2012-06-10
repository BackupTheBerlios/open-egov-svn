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

#include <OEG/Qt/Application.h>
#include <OEG/Qt/MessageBox.h>

#include "MainWindow.h"
#include "Server.h"

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv, "application-connector");

  app.setApplicationName(_("Application Connector"), "0.1");
  app.setApplicationBuildData(__DATE__, __TIME__);

  // This is important, because else the closing of a QMessageBox will
  // terminate the application, if there are no other open windows!

  app.setQuitOnLastWindowClosed(false);

  Server server;

  if (! server.start()) {
    QMessageBox::critical(0, qApp->applicationName(),
                          QString(_("Unable to start the server: %1.")).arg(server.errorString()));
    QCoreApplication::quit();
    return 2;
  }

  MainWindow win;
  win.show();

  return app.exec();
}

