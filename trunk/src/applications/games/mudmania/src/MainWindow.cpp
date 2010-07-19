// $Id:$

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
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();
  createDockWidgets();

  setWindowTitle("Builder");
  setWindowIcon(QIcon("icon.png"));
}

void MainWindow::createActions()
{
}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));

}

void MainWindow::createToolBars()
{
  QToolBar *fileToolBar = addToolBar(_("File"));

}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(_("Ready."));
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::setTitle(const QString &title)
{
  m_title = title;
}

QString MainWindow::title() const
{
  return m_title;
}

