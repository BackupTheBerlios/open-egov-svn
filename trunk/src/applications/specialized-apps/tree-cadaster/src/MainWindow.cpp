// $Id$
//
// Open-eGovernment
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

#include "MainWindow.h"

#include <OEG/GIS/MapWidget.h>

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

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_tabs = new QTabWidget(this);
  m_tabs->addTab(new QLabel("Last Changes"), _("&History"));
  m_map = new OEG::GIS::MapWidget(this);
  m_tabs->addTab(m_map, _("&Map"));
  m_tabs->addTab(new QLabel("Reports"), _("&Reports"));
  m_tabs->setCurrentIndex(0);  // better use prefs.

  setCentralWidget(m_tabs);

}

MainWindow::~MainWindow()
{
  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::createActions()
{
  QAction *a;

  OEG::Qt::MainWindow::createActions();

  a = standardAction("zoom_in");
  if (a) {
    
    connect(a, SIGNAL(triggered()), this, SLOT(action_zoom_in()));
  }

#if 0
  a = new QAction("xyz", this);
  if (! a)
    return 0;

  a->setObjectName(baseName);
  if (baseName.length() > 0)
    a->setIcon(QIcon(baseName));
  a->setShortcut(keySequence);
  a->setToolTip(info);
  a->setStatusTip(info);
#endif
}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  //fileMenu->addSeparator();
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

  //t->addAction(standardAction("reload"));
}

void MainWindow::createStatusBar()
{
#if 0
  QStatusBar *sb = this->statusBar();

  m_number_of_processes = new QLabel(" 000 ");
  m_number_of_processes->setMinimumSize(m_number_of_processes->sizeHint());
  m_number_of_processes->setAlignment(Qt::AlignCenter);
  m_number_of_processes->setToolTip(_("The number of processes."));
  sb->addPermanentWidget(m_number_of_processes);

  m_current_time = new QLabel(" 00:00:00 ");
  m_current_time->setMinimumSize(m_current_time->sizeHint());
  m_current_time->setAlignment(Qt::AlignCenter);
  m_current_time->setToolTip(_("The current time."));
  sb->addPermanentWidget(m_current_time);
#endif

  OEG::Qt::MainWindow::createStatusBar();
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

