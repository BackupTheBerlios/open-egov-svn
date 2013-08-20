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

#include <OEG/GIS/MapWidget.h>
#include <OEG/Qt/Application.h>

#include <QAction>
#include <QApplication>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QDockWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSet>
#include <QStatusBar>
#include <QTabWidget>
#include <QTime>
#include <QTimer>
#include <QToolBar>
#include <QIcon>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_tab_history = new QLabel(this);
  m_tabs = new QTabWidget(this);
  m_tabs->addTab(m_tab_history, _("&History"));
  m_map = new OEG::GIS::MapWidget(this);
  if (! m_map)
    return;
  m_tabs->addTab(m_map, _("&Map"));
  m_tabs->addTab(new QLabel("Reports"), _("&Reports"));
  m_tabs->setCurrentIndex(0);  // better use prefs.

  setCentralWidget(m_tabs);

  // Init tab contents.
  QString s;
  s += "<h1>" + qApp->applicationName() + "</h1>";
  s += "Version: " + qApp->applicationVersion() + "<br>";
  s += "<h1>" + QString(_("Last Changes")) + "</h1>";
  m_tab_history->setText(s);

  m_map->setZoom(11);
  m_map->setArea(11.389, 52.243, 11.877, 52.033);
}

MainWindow::~MainWindow()
{
  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::createActions()
{
  QAction *action;

  OEG::Qt::MainWindow::createActions();

  action = standardAction(ZoomIn);
  if (action) {
    
    connect(action, SIGNAL(triggered()), this, SLOT(action_zoom_in()));
  }

#if 0
  action = new QAction("xyz", this);
  if (! action)
    return 0;

  action->setObjectName(baseName);
  if (baseName.length() > 0)
    action->setIcon(QIcon(baseName));
  action->setShortcut(keySequence);
  action->setToolTip(info);
  action->setStatusTip(info);
#endif
}

void MainWindow::createStatusBar()
{
  OEG::Qt::MainWindow::createStatusBar();

  m_number_of_trees = new QLabel(" 000000 ");
  m_number_of_trees->setMinimumSize(m_number_of_trees->sizeHint());
  m_number_of_trees->setAlignment(Qt::AlignCenter);
  m_number_of_trees->setToolTip(_("The number of trees in the database."));
  statusBar()->addPermanentWidget(m_number_of_trees);
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = getStandardMenu(FileMenu);
  //menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(SettingsMenu);
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()), this, SLOT(commonSettings()));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *a;
  QToolBar *t;

  t = addToolBar(_("File"));
  a = standardAction(Exit);
  a->setShortcuts(QKeySequence::Quit);
  t->addAction(a);

  //t->addAction(standardAction("reload"));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu *menu = new QMenu(this);
  Q_CHECK_PTR(menu);
  if (! menu)
    return;

  menu->addSeparator();
  menu->addAction("&Copy",                  this, SLOT(action_copy_details()),      QKeySequence(_("Ctrl+C")));

  menu->exec(event->globalPos());
  delete menu; menu = 0;
}

