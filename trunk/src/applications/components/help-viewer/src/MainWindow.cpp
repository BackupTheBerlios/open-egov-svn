// $Id$

#include "MainWindow.h"

#include <OEG/Qt/ToolProvider.h>

#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  createAll();

  setWindowIcon(QIcon("icon.png"));
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

}

void MainWindow::createToolBars()
{
  QToolBar *fileToolBar = addToolBar(tr("File"));

}

void MainWindow::createDockWidgets()
{
}

