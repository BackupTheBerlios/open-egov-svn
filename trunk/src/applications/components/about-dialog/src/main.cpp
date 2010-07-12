// $Id$

#include <OEG/Qt/Application.h>

#include "MainWindow.h"

#define MODULE_ID(id) static const char Ident[] = id;

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  MODULE_ID("$Id$")

  MainWindow *mw = new MainWindow();

  return app.exec();
}

