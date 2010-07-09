// $Id$

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  show();
}

void MainWindow::setTitle(const QString &title)
{
  m_title = title;
}

QString MainWindow::title() const
{
  return m_title;
}

