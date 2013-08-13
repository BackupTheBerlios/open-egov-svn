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

#include "MainWindow.h"
#include "MIDI.h"

#include <OEG/Qt/TabbedMenuBar.h>

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


  //setCentralWidget();

  createAll();

}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *menu;

  menu = menuBar()->addMenu(_("&File"));
  menu->addAction(standardAction(Open));
  menu->addAction(standardAction(Close));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Open));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));

}

void MainWindow::createDockWidgets()
{
}

void MainWindow::standardActionOpen()
{
  MIDI midi;

  midi.loadFile("I:\\Projekte\\open-egov\\src\\applications\\multimedia\\midi-player\\src\\Beethoven - For Elise.mid");

}

