// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <OEG/Qt/ToolProvider.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>

#include "MainWindow.h"

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
  QMenu *menu;

  menu = menuBar()->addMenu(_("&File"));
  menu->addAction(standardAction(New));
  menu->addAction(standardAction(Edit));
  menu->addAction(standardAction(Print));
  menu->addAction(standardAction(Edit));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = menuBar()->addMenu(_("&Edit"));
  menu->addAction(standardAction(Undo));
  menu->addAction(standardAction(Redo));
  menu->addSeparator();
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));
  menu->addAction(standardAction(Delete));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(New));
  toolbar->addAction(standardAction(Edit));
  toolbar->addAction(standardAction(Print));
  toolbar->addAction(standardAction(Edit));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Undo));
  toolbar->addAction(standardAction(Redo));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Cut));
  toolbar->addAction(standardAction(Copy));
  toolbar->addAction(standardAction(Paste));
  toolbar->addAction(standardAction(Delete));
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

