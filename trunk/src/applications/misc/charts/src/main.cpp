// $Id:$

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
    MainWidget *w = new MainWidget();
    w->setPlainText("Text");
    w->resize(400, 200);
    w->show();
  }

  return app.exec();
}

