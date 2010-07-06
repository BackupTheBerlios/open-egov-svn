// $Id$

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow *mw = new MainWindow();

  return app.exec();
}

