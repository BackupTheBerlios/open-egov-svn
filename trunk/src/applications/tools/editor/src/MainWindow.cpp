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
#include <OEG/Qt/ToolProvider.h>

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QIcon>
#include <QTabWidget>

#include "PluginInterface.h"
#include "TextEditor.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_tabs = new OEG::Qt::TabWidget(this);
  if (! m_tabs) {
    qDebug() << "No tab widget.";
    return;
  }

  m_tabs->setMovable(true);
  m_tabs->setDocumentMode(true);
  m_tabs->setTabsClosable(false);
  m_tabs->setUsesScrollButtons(true);
  m_tabs->separateCloseTabButton(_("Close Tab"));
  standardActionNew();
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

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  fileMenu->addAction(standardAction(New));
  fileMenu->addAction(standardAction(Open));
  fileMenu->addAction(standardAction(Reload));
  fileMenu->addAction(standardAction(Save));
  fileMenu->addAction(standardAction(SaveAs));
  fileMenu->addAction(standardAction(Close));
  fileMenu->addSeparator();
  fileMenu->addAction(standardAction(Print));
  fileMenu->addAction(standardAction(PrintPreview));
  fileMenu->addAction(standardAction(PrintSettings));
  fileMenu->addSeparator();
  fileMenu->addAction(standardAction(Exit));

  QMenu *editMenu = menuBar()->addMenu(_("&Edit"));
  editMenu->addAction(standardAction(Undo));
  editMenu->addAction(standardAction(Redo));
  editMenu->addSeparator();
  editMenu->addAction(standardAction(Cut));
  editMenu->addAction(standardAction(Copy));
  editMenu->addAction(standardAction(Paste));
  editMenu->addSeparator();
  editMenu->addAction(standardAction(SelectAll));
  editMenu->addSeparator();
  editMenu->addAction(standardAction(Delete));

  QMenu *extensionsMenu = menuBar()->addMenu(_("E&xtensions"));
  extensionsMenu->addAction("Test");

  addHelpMenu();
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
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::loadPlugins()
{
  QString baseName = applicationBaseName();
  QDir pluginsDir(qApp->applicationDirPath(), "*.dll;*.so");  // Ignore .a files.

  if (pluginsDir.dirName().toLower() == "bin")
    pluginsDir.cdUp();
  pluginsDir.cd("plugins/" + baseName);

  qDebug() << "Loading Plugins from: " << pluginsDir.absolutePath();

  PluginInterface *interface;
  QObject *plugin;

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    plugin = pluginLoader.instance();
    if (plugin) {
      interface = qobject_cast<PluginInterface *>(plugin);
      if (interface) {
        if (interface->pluginApplicationName() != baseName) {
          qWarning() << "Application base names from plugin and application do not match:";
          qWarning() << " plugin file name:" << fileName;
          qDebug() << " application base name:" << baseName;
          qDebug() << " plugin application name:" << interface->pluginApplicationName();
        }
        else {
          m_plugins.append(interface);
        }
      }
    }
    else {
      qDebug() << "Plugin not found: " << fileName;
    }
  }

  qDebug() << "Number of Plugins found: " << m_plugins.count();
}

void MainWindow::standardActionClose()
{
  m_tabs->closeTab();
}

void MainWindow::standardActionOpen()
{
}

void MainWindow::standardActionNew()
{
  TextEditor *editor = new TextEditor(this);

  if (! editor)
    return;

  editor->highlightCurrentLine();
  editor->setLineNumbersWidth(50);
  editor->showLineNumbers();

  m_tabs->addTab(editor, _("Unnamed"));
}

void MainWindow::standardActionPrint()
{
}

