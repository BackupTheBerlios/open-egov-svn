// $Id$

#include "MainWindow.h"

#include <OEG/Qt/ToolProvider.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  fileMenu->addAction(standardAction("exit"));
}

void MainWindow::createToolBars()
{
  QAction  *a;
  QToolBar *t;

  t = addToolBar(_("File"));
  a = standardAction("exit");
  a->setShortcuts(QKeySequence::Quit);
  t->addAction(a);

}

void MainWindow::createDockWidgets()
{
}

