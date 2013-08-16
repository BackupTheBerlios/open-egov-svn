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

#include <OEG/Qt/Application.h>
#include <OEG/Qt/TabbedMenuBar.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QAction>
#include <QIcon>
#include <QDir>
#include <QPluginLoader>
#include <QString>

#include <QGraphicsView>
#include <QGraphicsItem>

#include "SchematicsScene.h"
#include "SchematicsTab.h"
#include "SimulationTab.h"
#include "ProjectTab.h"
#include "PartListTab.h"
#include "PCBTab.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_tabs = new QTabWidget(this);
  if (! m_tabs)
    return;

  m_tab_project    = new ProjectTab(this);
  m_tab_part_list  = new PartListTab(this);
  m_tab_schematics = new SchematicsTab(this);
  m_tab_pcb_layout = new PCBTab(this);
  m_tab_simulation = new SimulationTab(this);
  m_tab_notes      = new QTextEdit(this);

  m_tabs->addTab(m_tab_project,    _("&Project"));
  m_tabs->addTab(m_tab_part_list,  _("Part &List"));
  m_tabs->addTab(m_tab_schematics, _("&Schematics"));
  m_tabs->addTab(m_tab_pcb_layout, _("PCB &Layout"));
  m_tabs->addTab(m_tab_simulation, _("Si&mulation"));
  m_tabs->addTab(m_tab_notes,      _("&Notes"));
  m_tabs->setCurrentIndex(0);                              // Better use prefs.

  setCentralWidget(m_tabs);

  loadPlugins();
}

MainWindow::~MainWindow()
{
  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createStatusBar()
{

  OEG::Qt::MainWindow::createStatusBar();
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
  menu->addAction(standardAction(Open));
  menu->addAction(standardAction(Save));
  menu->addAction(standardAction(SaveAs));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(standardAction(Undo));
  menu->addAction(standardAction(Redo));
  menu->addSeparator();
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));
  menu->addSeparator();
  menu->addAction(standardAction(Delete));

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
  toolbar->addAction(standardAction(Open));
  toolbar->addAction(standardAction(Save));
  toolbar->addAction(standardAction(SaveAs));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Undo));
  toolbar->addAction(standardAction(Redo));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Cut));
  toolbar->addAction(standardAction(Copy));
  toolbar->addAction(standardAction(Paste));
  toolbar->addAction(standardAction(Delete));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Preferences));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));

  toolbar = addToolBar(_("Schematics"));
  toolbar->addAction("Rotate CW");
  toolbar->addAction("Rotate CCW");
  toolbar->addSeparator();
  toolbar->addAction(standardAction(ZoomIn));
  toolbar->addAction(standardAction(ZoomNormal));
  toolbar->addAction(standardAction(ZoomOut));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::loadPlugins()
{
  QString baseName = dynamic_cast<OEG::Qt::Application *>(qApp)->baseName();
  QDir pluginsDir(qApp->applicationDirPath(), "*.dll;*.so");  // Ignore .a files.

  if (pluginsDir.dirName().toLower() == "bin")
    pluginsDir.cdUp();
  pluginsDir.cd("plugins/" + baseName);

  qDebug() << "Loading Plugins from: " << pluginsDir.absolutePath();

  PluginInterface *pluginInterface;
  QObject *plugin;
  QWidget *gui;

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    plugin = pluginLoader.instance();
    if (plugin) {
      pluginInterface = qobject_cast<PluginInterface *>(plugin);
      if (pluginInterface) {
        if (pluginInterface->pluginApplicationName() != baseName) {
          qWarning() << "Application base names from plugin and application do not match:";
          qWarning() << " plugin file name:" << fileName;
          qDebug() << " application base name:" << baseName;
          qDebug() << " plugin application name:" << pluginInterface->pluginApplicationName();
        }
        else {
          m_plugins.append(pluginInterface);

          QGraphicsItem *item = pluginInterface->createGraphicsItem();
          m_tab_schematics->scene()->addItem(item);
          item->setPos(10, 10);
          item->show();
          item->setFocus();

          m_tab_schematics->scene()->addText("1234567--------")->setPos(10, 100);

          //gui = pluginInterface->createGUI(this);
          //if (gui) {
          //  gui->show();
          //}
        }
      }
    }
    else {
      qDebug() << "Plugin not found: " << fileName;
    }
  }

  qDebug() << "Number of Plugins found: " << m_plugins.count();
}

