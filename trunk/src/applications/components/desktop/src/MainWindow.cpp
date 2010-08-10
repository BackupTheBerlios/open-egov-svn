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

DesktopWidget::DesktopWidget(QWidget *parent /*=0*/)
 : QWidget(0, Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnBottomHint)
 // OEG::Qt::MainWindow(parent, Qt::Desktop | Qt::FramelessWindowHint)
{
  setGeometry(parent->geometry());
  setFixedSize(parent->size());
  setBackgroundRole(QPalette::Window);

  m_menubar = new QMenuBar(this);

  m_layout = new QVBoxLayout;
  //m_layout->addWidget(m_menubar);
  m_layout->setMenuBar(m_menubar);
  setLayout(m_layout);

  createActions();
  createMenus();
  loadPlugins();
}

void DesktopWidget::createActions()
{
  m_action_process_list = new QAction(_("&Process List"), this);
  m_action_process_list->setShortcut(QKeySequence(_("Ctrl+Alt+Del")));
  m_action_process_list->setStatusTip(_("Open the process list."));
  connect(m_action_process_list, SIGNAL(triggered()), this, SLOT(actionProcessList()));

  m_action_exit = new QAction(_("E&xit"), this);
  m_action_exit->setShortcut(QKeySequence(_("Ctrl+Q")));
  m_action_exit->setStatusTip(_("Exit the application"));
  connect(m_action_exit, SIGNAL(triggered()), this, SLOT(close()));

  m_action_help = new QAction(_("&Help"), this);
  m_action_help->setStatusTip(_("Open the help viewer"));
  connect(m_action_help, SIGNAL(triggered()), this, SLOT(helpViewer()));

  m_action_about_app = new QAction(_("&About"), this);
  m_action_about_app->setStatusTip(_("Show the application's About box"));
  connect(m_action_about_app, SIGNAL(triggered()), this, SLOT(about()));

  m_action_about_qt = new QAction(_("About &Qt"), this);
  m_action_about_qt->setStatusTip(_("Show the Qt library's About box"));
  connect(m_action_about_qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void DesktopWidget::createMenus()
{
  m_menu_file = m_menubar->addMenu(_("&File"));
  m_menu_file->addAction(m_action_process_list);
  m_menu_file->addSeparator();
  m_menu_file->addAction(m_action_exit);

  m_menubar->addSeparator();

  m_menu_help = m_menubar->addMenu(_("&Help"));
  m_menu_help->addAction(m_action_help);
  m_menu_help->addSeparator();
  m_menu_help->addAction(m_action_about_app);
  m_menu_help->addAction(m_action_about_qt);
}

void DesktopWidget::loadPlugins()
{
  QDir pluginsDir(qApp->applicationDirPath());

  if (pluginsDir.dirName().toLower() == "bin")
    pluginsDir.cdUp();
  pluginsDir.cd("plugins/desktop");

  DesktopPluginInterface *pluginInterface;
  QObject *plugin;
  QWidget *gui;

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    plugin = pluginLoader.instance();
    if (plugin) {
      pluginInterface = qobject_cast<DesktopPluginInterface *>(plugin);
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

void DesktopWidget::actionProcessList()
{
  OEG::Qt::Application::runComponent("process-list");
}

void DesktopWidget::helpViewer()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "index");
}

void DesktopWidget::about()
{
  //OEG::Qt::ProcessList pl;
  //pl.update();

  OEG::Qt::Application::runComponent("about-dialog");
}

void DesktopWidget::closeEvent(QCloseEvent *event)
{
//    if (maybeSave()) {
//        writeSettings();
//       event->accept();
//    } else {
//        event->ignore();
//    }
}

