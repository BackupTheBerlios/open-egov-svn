// $Id$

#include <OEG/Qt/Application.h>

#include "MainWindow.h"

MODULE_INFO("File: " __FILE__ ", Build: " __DATE__)

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  MainWindow *mw __attribute__ ((__unused__)) = new MainWindow();

  return app.exec();
}

