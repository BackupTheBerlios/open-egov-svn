// $Id$
//
// Open-eGovernment
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

#include <OEG/Qt/Application.h>

#include <QSettings>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  app.setApplicationName(_("Map Viewer"));
  app.setOrganizationName(_("G.A.S.I."));
  app.setOrganizationDomain(_("open-egov.de"));
  app.setApplicationVersion(_("0.1"));
  app.setApplicationBuildData(__DATE__, __TIME__);
  app.setHomepage(_("http://www.open-egov.de/"));

  QSettings settings(app.organizationName(), app.applicationName());
  if (settings.status() != QSettings::NoError) {
    qDebug() << __FILE__ ": settings error: " << settings.status();
  }

  MainWindow mw;
  mw.show();

  return app.exec();
}
