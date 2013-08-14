// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <OEG/Qt/TabbedMenuBar.h>

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QVBoxLayout>

#include <QDebug>

#include <OEG/Qt/MessageBox.h>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setObjectName("MainWindow");
  setWindowIcon(QIcon("icon.png"));
  setWindowTitle(_("File Viewer"));

  setCentralWidget(new QWidget(this));

  createAll();

  //QTimer::singleShot(200, this, SLOT(updateFileSystemViews()));

  //connect(m_dock_buttons,   SIGNAL(sendCommand(const QString &)),
  //        m_folder_manager, SLOT(runCommand(const QString &)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = getStandardMenu(FileMenu);
  menu->addAction(_("Update contents"), this, SLOT(updateFileSystemViews()));
  menu->addSeparator();

  action = menu->addAction(_("Load ..."));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(loadXXX()));
  action = menu->addAction(_("Save ..."));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(saveXXX()));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createDockWidgets()
{
}

