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

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_map = new OEG::GIS::MapWidget(this);
  if (! m_map)
    return;
  connect(m_map, SIGNAL(coordinatesAtMouse(double, double)),
          this,  SLOT(receiveCoordinatesAtMouse(double, double)));
  m_map->setZoom(11);
  m_map->setArea(11.389, 52.243, 11.877, 52.033);
  setCentralWidget(m_map);
}

MainWindow::~MainWindow()
{
  if (m_map) {
    delete m_map; m_map = 0;
  }
}

void MainWindow::createActions()
{
  QAction *a;

  OEG::Qt::MainWindow::createActions();

  a = standardAction(ZoomIn);
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

void MainWindow::createStatusBar()
{
  OEG::Qt::MainWindow::createStatusBar();

  m_coordinates = new QLabel(" 00.0000, 00.0000 ");
  m_coordinates->setMinimumSize(m_coordinates->sizeHint());
  m_coordinates->setAlignment(Qt::AlignCenter);
  m_coordinates->setToolTip(_("Current coordinates."));
  statusBar()->addPermanentWidget(m_coordinates);
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

  menu = menuBar()->addMenu(_("&Map"));
  menu->addAction(standardAction(ZoomNormal));
  menu->addAction(standardAction(ZoomIn));
  menu->addAction(standardAction(ZoomOut));
  //menu->addSeparator();
  //menu->addAction(standardAction("engine_google"));
  //menu->addAction(standardAction("engine_osm"));

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
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::receiveCoordinatesAtMouse(double x, double y)
{
  m_coordinates->setText(QString(_("%1 , %2")).arg(x).arg(y));
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

