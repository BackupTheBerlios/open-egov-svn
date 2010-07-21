// $Id$

#include <OEG/Qt/Application.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  app.setApplicationName(_("Help Viewer"));
  app.setOrganizationName(_("G.A.S.I."));
  app.setOrganizationDomain(_("open-egov.de"));

  MainWindow mw;
  mw.show();

  return app.exec();
}

