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
#include <QAxFactory>

#include "MainWidget.h"

QAXFACTORY_BEGIN(
    "{E2323DE8-873E-4725-A80C-47E2626A0556}",    // Type library ID.
    "{558BACA5-36D0-492f-AB78-DF991F111D1D}"     // Application ID.
  )
  QAXCLASS(MainWidget)
QAXFACTORY_END()

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if (! QAxFactory::isServer()) {                // Create and show main window.
    MainWidget *w = new MainWidget;
    w->setPlainText("Text");
    w->resize(400, 200);
    w->show();
  }

  return app.exec();
}

