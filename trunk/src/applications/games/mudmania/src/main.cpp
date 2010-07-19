// $Id:$

#include <OEG/Qt/Application.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  MainWindow *mw = new MainWindow();
  mw->show();

  return app.exec();
}

