// $Id$

#include <OEG/Qt/Application.h>

#include <QSettings>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  app.setApplicationName(_("Address Book"));
  app.setOrganizationName(_("G.A.S.I."));
  app.setOrganizationDomain(_("open-egov.de"));

  QSettings settings(app.organizationName(), app.applicationName());
  if (settings.status() != QSettings::NoError) {
    qDebug() << __FILE__ ": settings error: " << settings.status();
  }

  MainWindow *mw = new MainWindow();
  mw->show();

  return app.exec();
}

