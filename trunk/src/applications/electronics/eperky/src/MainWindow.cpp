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

#include <OEG/Qt/ToolProvider.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QAction>
#include <QIcon>

#include <QGraphicsView>

#include "SchematicsScene.h"
#include "SchematicsView.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_schematics_scene = new SchematicsScene;

  m_tabs = new QTabWidget(this);
  if (! m_tabs)
    return;

  m_tab_project    = new QWidget(this);
  m_tab_part_list  = new QWidget(this);
  m_tab_schematics = new SchematicsView(this);
  m_tab_pcb_layout = new QWidget(this);
  m_tab_simulation = new QWidget(this);
  m_tab_notes      = new QTextEdit(this);

  m_tabs->addTab(m_tab_project,    _("&Project"));
  m_tabs->addTab(m_tab_part_list,  _("Part &List"));
  m_tabs->addTab(m_tab_schematics, _("&Schematics"));
  m_tabs->addTab(m_tab_pcb_layout, _("PCB &Layout"));
  m_tabs->addTab(m_tab_simulation, _("Si&mulation"));
  m_tabs->addTab(m_tab_notes,      _("&Notes"));
  m_tabs->setCurrentIndex(0);                              // better use prefs.

  setCentralWidget(m_tabs);
}

MainWindow::~MainWindow()
{
  if (m_schematics_scene) {
    delete m_schematics_scene; m_schematics_scene = 0;
  }

  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  fileMenu->addAction(standardAction(Exit));

  addHelpMenu();
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

