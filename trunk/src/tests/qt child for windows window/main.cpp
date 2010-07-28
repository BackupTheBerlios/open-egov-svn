// $Id$

#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>

#include "WinWidget.h"

#include <windows.h>

int main (int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setOrganizationName("G.A.S.I.");
  app.setOrganizationDomain("gasi.de");
  app.setApplicationName("Test of subclassing a Windows native window");

  WinWidget w(NULL, TEXT("Eigene Dateien"));     // Grab a explorer.exe
  //WinWidget w(handle);
  w.show();                                      // Show child widgets.

  QLabel *l = new QLabel("Testlabel", &w);
  l->show();

  return app.exec();
}

