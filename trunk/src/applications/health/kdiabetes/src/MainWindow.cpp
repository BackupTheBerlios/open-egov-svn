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

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  QWidget *w = new QWidget(this);

  setCentralWidget(w);

  createAll();
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

  QAction *action;
  QString s;

  action = standardAction(New);
  action->setText(_("&New Data"));
  s = _("Enter new data.");
  action->setToolTip(s);
  action->setStatusTip(s);
  connect(action, SIGNAL(triggered()),
          this,   SLOT(newDataAction()));
}

void MainWindow::createStatusBar()
{
  OEG::Qt::MainWindow::createStatusBar();

  m_sb_clock = new QLabel("00.00.00 00:00:00");
  m_sb_clock->setMinimumSize(m_sb_clock->sizeHint());
  m_sb_clock->setAlignment(Qt::AlignCenter);
  m_sb_clock->setToolTip(_("Current data and time."));
  statusBar()->addPermanentWidget(m_sb_clock);

  //updateStatusBar();
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = getStandardMenu(FileMenu);
  menu->addAction(standardAction(New));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));

  menu = menuBar()->addMenu(_("&Analyze"));

  menu = getStandardMenu(SettingsMenu);
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()), this, SLOT(commonSettings()));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(New));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createTabbedMenuBar()
{
}

