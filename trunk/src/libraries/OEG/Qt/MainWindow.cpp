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

#include <OEG/Common.h>
#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/ToolProvider.h>

#include <QAction>
#include <QApplication>
#include <QKeySequence>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLatin1String>

using namespace OEG::Qt;
using namespace Qt;

MainWindow::MainWindow(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QMainWindow(parent, flags), m_tool_provider(0)
{
  setWindowTitle(QCoreApplication::applicationName());

  resize(400, 300);

  //createAll();
}

MainWindow::~MainWindow()
{
  while (! m_actions.isEmpty())
    delete m_actions.takeFirst();

  if (m_tool_provider) {
    delete m_tool_provider; m_tool_provider = 0;
  }
}

void MainWindow::createAll()
{
  createActions();
  createDockWidgets();
  createMenus();
  createStatusBar();
  createToolBars();
  createToolProvider();
}

void MainWindow::createActions()
{
  standardAction("exit");
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(_("Ready."));
}

void MainWindow::createToolBars()
{
}

void MainWindow::createToolProvider()
{
  m_tool_provider = new ToolProvider(this);
  m_tool_provider->show();

}

QAction *MainWindow::addStandardAction(const QString &baseName, const QString &title,
                                       const QString &info, const QString &keySequence /*=QString()*/)
{
  QAction *a = new QAction(title, this);
  if (! a)
    return 0;

  a->setObjectName(baseName);
  if (baseName.length() > 0)
    a->setIcon(QIcon(baseName));
  a->setShortcut(keySequence);
  a->setToolTip(info);
  a->setStatusTip(info);

  m_actions.append(a);

  return a;
}

QAction *MainWindow::standardAction(const QString &baseName)
{
  QAction *a;

  for (int i=0; i<m_actions.size(); i++) {
    a = m_actions.at(i);
    if (a->objectName() == baseName)
      return a;
  }

  if (baseName == "exit") {
    a = addStandardAction(baseName, _("E&xit"), _("Exit the application."), _("Alt+F4"));
    connect(a, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    return a;
  }
  if (baseName == "reload") {
    a = addStandardAction(baseName, _("&Reload"), _("Reloads data."), _("F5"));
    return a;
  }
  if (baseName == "help") {
    a = addStandardAction(baseName, _("&Help ..."), _("Open the help window."), _("F1"));
    return a;
  }
  if (baseName == "about_app") {
    a = addStandardAction(baseName, _("About &App ..."), _("Information about this appliciation."));
    return a;
  }
  if (baseName == "about_qt") {
    a = addStandardAction(baseName, _("About &Qt ..."), _("Information about the Qt framework."));
    return a;
  }

  // If at least an action name is given, we'll return an action object without additional settings.
  if (baseName.length() > 0) {
    qDebug() << "MainWindow::standardAction(): Unknown action name: " << baseName;
    return addStandardAction(baseName, _("Unnamed Action"), _("This action is unnamed and therefore without description."));
  }

  return 0;
}

QAction *MainWindow::standardAction(const StandardAction &action)
{
  return standardAction(standardActionName(action));
}

// This are the possible standard actions together with their base names. The names are needed to specify
// the associated SVG icon.

QString MainWindow::standardActionName(const StandardAction &action)
{
  if (action == AboutApp)              return QLatin1String("about_app");
  if (action == AboutQt)               return QLatin1String("about_qt");
  if (action == Close)                 return QLatin1String("close");
  if (action == Copy)                  return QLatin1String("copy");
  if (action == Cut)                   return QLatin1String("cut");
  if (action == Delete)                return QLatin1String("delete");
  if (action == Exit)                  return QLatin1String("exit");
  if (action == HelpContents)          return QLatin1String("help_contents");
  if (action == HelpIndex)             return QLatin1String("help_index");
  if (action == HelpSearch)            return QLatin1String("help_search");
  if (action == New)                   return QLatin1String("new");
  if (action == Open)                  return QLatin1String("open");
  if (action == Paste)                 return QLatin1String("paste");
  if (action == Plugins)               return QLatin1String("plugins");
  if (action == Preferences)           return QLatin1String("preferences");
  if (action == PreferencesColors)     return QLatin1String("preferences_colors");
  if (action == PreferencesCommon)     return QLatin1String("preferences_common");
  if (action == PreferencesFonts)      return QLatin1String("preferences_fonts");
  if (action == PreferencesShortcuts)  return QLatin1String("preferences_shortcuts");
  if (action == Print)                 return QLatin1String("print");
  if (action == PrintPreview)          return QLatin1String("print_preview");
  if (action == PrintSettings)         return QLatin1String("print_settings");
  if (action == Redo)                  return QLatin1String("redo");
  if (action == Reload)                return QLatin1String("reload");
  if (action == Save)                  return QLatin1String("save");
  if (action == SaveAs)                return QLatin1String("save_as");
  if (action == SelectAll)             return QLatin1String("select_all");
  if (action == Undo)                  return QLatin1String("undo");

  return "";
}

void MainWindow::addHelpMenu()
{
  QMenu *menu;

  menuBar()->addSeparator();

  menu = menuBar()->addMenu(_("&Help"));
  menu->addAction(standardAction("help"));
  menu->addSeparator();
  menu->addAction(standardAction("about_app"));
  menu->addAction(standardAction("about_qt"));
}

