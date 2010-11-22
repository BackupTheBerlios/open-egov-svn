// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

}

void MainWindow::createMenus()
{
  QMenu *menu;

  menu = menuBar()->addMenu(_("&File"));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = menuBar()->addMenu(_("&Edit"));
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
}

