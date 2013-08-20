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
#include <OEG/Qt/ProcessList.h>

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPluginLoader>
#include <QVBoxLayout>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent, /*Qt::Desktop |*/ Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnBottomHint)
{
  setGeometry(parent->geometry());
  setFixedSize(parent->size());
  setBackgroundRole(QPalette::Window);

  createAll();

  loadPlugins();
}

void MainWindow::createActions()
{
  m_action_process_list = new QAction(_("&Process List"), this);
  m_action_process_list->setShortcut(QKeySequence(_("Ctrl+Alt+Del")));
  m_action_process_list->setStatusTip(_("Open the process list."));
  connect(m_action_process_list, SIGNAL(triggered()), this, SLOT(actionProcessList()));
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
  menu->addAction(m_action_process_list);
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(SettingsMenu);
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()), this, SLOT(commonSettings()));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
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
        m_plugins.append(pluginInterface);

        gui = pluginInterface->createGUI(this);
        if (gui) {
          gui->show();
        }
      }
    }
  }

  qDebug() << "Plugins found: " << m_plugins.count();
}

void MainWindow::actionProcessList()
{
  OEG::Qt::Application::runComponent("process-list");
}

//OEG::Qt::ProcessList pl;
//pl.update();

void MainWindow::closeEvent(QCloseEvent *event)
{
//    if (maybeSave()) {
//        writeSettings();
//       event->accept();
//    } else {
//        event->ignore();
//    }
}

