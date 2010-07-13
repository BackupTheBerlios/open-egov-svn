// $Id$

#include <OEG/Qt/Application.h>

#include <QDesktopWidget>

#include "MainWindow.h" // DesktopWidget

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv);

  DesktopWidget dw(QApplication::desktop()->screen(0));
  dw.show();

  return app.exec();
}

