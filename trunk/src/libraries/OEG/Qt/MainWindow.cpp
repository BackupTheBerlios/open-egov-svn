// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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
#include <OEG/Qt/Application.h>
#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/TabbedMenuBar.h>
#include <OEG/Qt/DragAndDropHandler.h>

#include <QtPrintSupport>

#include <QAction>
#include <QGuiApplication>
#include <QKeySequence>
#include <QLatin1String>
#include <QLayout>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QPrinter>
#include <QStatusBar>

using namespace OEG::Qt;
using namespace Qt;

MainWindow::MainWindow(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QMainWindow(parent, flags), m_tabbed_menubar(0), m_printer(0)
{
  setWindowTitle(QCoreApplication::applicationName());
  setObjectName("MainWindow");
  setUnifiedTitleAndToolBarOnMac(true);

  resize(500, 400);

  m_data_storage_mode = DoNothing;

  // Initialize Drag and Drop.
  setAcceptDrops(true);
  installEventFilter(new DragAndDropHandler(this));

  //createAll();
}

MainWindow::~MainWindow()
{
  while (! m_actions.isEmpty())
    delete m_actions.takeFirst();

  if (m_tabbed_menubar) {
    delete m_tabbed_menubar; m_tabbed_menubar = 0;
  }

  if (m_printer) {
    delete (QPrinter *) m_printer; m_printer = 0;
  }
}

void MainWindow::createAll()
{
  createActions();
  createDockWidgets();
  createMenus();
  createStatusBar();
  createToolBars();
  createTabbedMenuBar();
}

void MainWindow::createActions()
{
  standardAction(Exit);
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(_("Ready."), 2000);
}

void MainWindow::createToolBars()
{
}

void MainWindow::createTabbedMenuBar()
{
  m_tabbed_menubar = new TabbedMenuBar(this);
  m_tabbed_menubar->hide();

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

QAction *MainWindow::createStandardAction(const StandardAction &action, const QString &baseName)
{
  QAction *a = 0;

  switch (action) {
    case AboutApp:
      a = addStandardAction(baseName, _("About &App ..."), _("Information about this appliciation."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionAboutApp()));
      break;
    case AboutQt:
      a = addStandardAction(baseName, _("About &Qt ..."), _("Information about the Qt framework."));
      connect(a, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
      break;
    case Clear:
      a = addStandardAction(baseName, _("Clear"), _("Clear output window."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionClear()));
      break;
    case ConnectToggle:
      a = addStandardAction(baseName, _("Connect"), _("Open a new Connection."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionConnectToggle()));
      break;
    case Close:
      a = addStandardAction(baseName, _("&Close"), _("Close."), _("Ctrl+W"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionClose()));
      break;
    case Copy:
      a = addStandardAction(baseName, _("Copy"), _("Copy data."), _("Ctrl+C"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionCopy()));
      break;
    case Cut:
      a = addStandardAction(baseName, _("Cut"), _("Cut data."), _("Ctrl+X"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionCut()));
      break;
    case Delete:
      a = addStandardAction(baseName, _("Delete"), _("Delete data."), _("Del"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionDelete()));
      break;
    case Edit:
      a = addStandardAction(baseName, _("Edit"), _("Edit data."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionEdit()));
      break;
    case Exit:
      a = addStandardAction(baseName, _("E&xit"), _("Exit the application."), _("Alt+F4"));
      a->setShortcuts(QKeySequence::Quit);
      connect(a, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
      break;
    case GoToHomepage:
      a = addStandardAction(baseName, _("&Homepage ..."), _("Open the homepage in the standard browser."));
      break;
    case HelpContents:
      a = addStandardAction(baseName, _("&Help ..."), _("Open the help window with contents."), _("F1"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionHelpContents()));
      break;
    case HelpIndex:
      a = addStandardAction(baseName, _("Help &Index ..."), _("Open the help window with index."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionHelpIndex()));
      break;
    case HelpSearch:
      a = addStandardAction(baseName, _("Help &Search ..."), _("Open the help window with search."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionHelpSearch()));
      break;
    case HelpForum:
      a = addStandardAction(baseName, _("&Forum ..."), _("Open the webpage of an online-help forum."));
      break;
    case New:
      a = addStandardAction(baseName, _("&New"), _("Create new document."), _("Ctrl+N"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionNew()));
      break;
    case Open:
      a = addStandardAction(baseName, _("&Open"), _("Open existing document."), _("Ctrl+O"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionOpen()));
      break;
    case Paste:
      a = addStandardAction(baseName, _("Paste"), _("Paste data into document."), _("Ctrl+V"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionPaste()));
      break;
    case Plugins:
      a = addStandardAction(baseName, _("Plugins ..."), _("Open the plugin manager."));
      break;
    case Preferences:
      a = addStandardAction(baseName, _("&Preferences ..."), _("Open the preferences dialog."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionPreferences()));
      break;
    case PreferencesColors:
      a = addStandardAction(baseName, _("&Colors ..."), _("Open the preferences dialog for colors settings."));
      break;
    case PreferencesCommon:
      a = addStandardAction(baseName, _("&Common ..."), _("Open the preferences dialog for common settings."));
      break;
    case PreferencesFonts:
      a = addStandardAction(baseName, _("&Fonts ..."), _("Open the preferences dialog with fonts settings."));
      break;
    case PreferencesShortcuts:
      a = addStandardAction(baseName, _("&Shortcuts ..."), _("Open the preferences dialog with shortcuts settings."));
      break;
    case Print:
      a = addStandardAction(baseName, _("&Print"), _("Print document."), _("Ctrl+P"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionPrint()));
      break;
    case PrintPreview:
      a = addStandardAction(baseName, _("Print Preview ..."), _("Print preview."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionPrintPreview()));
      break;
    case PrintSettings:
      a = addStandardAction(baseName, _("Print Settings ..."), _("Print Settings."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionPrintSettings()));
      break;
    case Redo:
      a = addStandardAction(baseName, _("&Redo"), _("Redo changes."), _("Ctrl+Y"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionRedo()));
      break;
    case Reload:
      a = addStandardAction(baseName, _("&Reload"), _("Reload data."), _("F5"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionReload()));
      break;
    case ReportBug:
      a = addStandardAction(baseName, _("Report &Bug ..."), _("Open the bug report dialog."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionReportBug()));
      break;
    case Save:
      a = addStandardAction(baseName, _("Save"), _("Save the document."), _("Ctrl+S"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionSave()));
      break;
    case SaveAs:
      a = addStandardAction(baseName, _("Save &As ..."), _("Save document into a new file."), _("Ctrl+Alt+S"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionSaveAs()));
      break;
    case SelectAll:
      a = addStandardAction(baseName, _("Select &All"), _("Select all."), _("Ctrl+A"));
      break;
    case Undo:
      a = addStandardAction(baseName, _("&Undo"), _("Undo changes."), _("Ctrl+Z"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionUndo()));
      break;
    case ZoomFitWidth:
      a = addStandardAction(baseName, _("Zoom Fit Width"), _("Zoom document until it fits into the window with."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionZoomFitWidth()));
      break;
    case ZoomFitWindow:
      a = addStandardAction(baseName, _("Zoom Fit Window"), _("Zoom document until it fits into the window."));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionZoomFitWindow()));
      break;
    case ZoomIn:
      a = addStandardAction(baseName, _("Zoom In"), _("Zoom into document."), _("Ctrl++"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionZoomIn()));
      break;
    case ZoomOut:
      a = addStandardAction(baseName, _("Zoom Out"), _("Zoom out of document."), _("Ctrl+-"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionZoomOut()));
      break;
    case ZoomNormal:
      a = addStandardAction(baseName, _("Zoom Normal"), _("Set normal zoom value."), _("Ctrl+Shift+-"));
      connect(a, SIGNAL(triggered()), this, SLOT(standardActionZoomNormal()));
      break;
    default:
      // If at least an action name is given, we'll return an action object without additional settings.
      if (baseName.length() > 0) {
        qDebug() << "MainWindow::standardAction(): Unknown action name: " << baseName;
        a = addStandardAction(baseName, _("Unnamed Action"),
                              _("This action is unnamed and therefore without description."));
      }
      break;
  }

  return a;
}

QAction *MainWindow::findStandardAction(const QString &baseName)
{
  QAction *a;

  if (baseName.length() <= 0)
    return 0;

  for (int i=0; i<m_actions.size(); i++) {       // Return action, if it already exists.
    a = m_actions.at(i);
    if (a->objectName() == baseName)
      return a;
  }

  return 0;
}

QAction *MainWindow::standardAction(const StandardAction &action)
{
  QString n;
  QAction *a;

  n = standardActionName(action);
  a = findStandardAction(n);
  if (a)
    return a;

  return createStandardAction(action, n);
}

// This are the possible standard actions together with their base names.
// The names are needed e.g. to specify the associated SVG icon.

QString MainWindow::standardActionName(const StandardAction &action)
{
  if (action == AboutApp)              return QLatin1String("about_app");
  if (action == AboutQt)               return QLatin1String("about_qt");
  if (action == Clear)                 return QLatin1String("clear");
  if (action == ConnectToggle)         return QLatin1String("connect_toggle");
  if (action == Close)                 return QLatin1String("close");
  if (action == Copy)                  return QLatin1String("copy");
  if (action == Cut)                   return QLatin1String("cut");
  if (action == Delete)                return QLatin1String("delete");
  if (action == Edit)                  return QLatin1String("edit");
  if (action == Exit)                  return QLatin1String("exit");
  if (action == GoToHomepage)          return QLatin1String("go_to_homepage");
  if (action == HelpContents)          return QLatin1String("help_contents");
  if (action == HelpIndex)             return QLatin1String("help_index");
  if (action == HelpSearch)            return QLatin1String("help_search");
  if (action == HelpForum)             return QLatin1String("help_forum");
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
  if (action == ReportBug)             return QLatin1String("report_bug");
  if (action == Save)                  return QLatin1String("save");
  if (action == SaveAs)                return QLatin1String("save_as");
  if (action == SelectAll)             return QLatin1String("select_all");
  if (action == Undo)                  return QLatin1String("undo");
  if (action == ZoomFitWidth)          return QLatin1String("zoom_fit_width");
  if (action == ZoomFitWindow)         return QLatin1String("zoom_fit_window");
  if (action == ZoomIn)                return QLatin1String("zoom_in");
  if (action == ZoomOut)               return QLatin1String("zoom_out");
  if (action == ZoomNormal)            return QLatin1String("zoom_normal");

  return "";
}

void MainWindow::addSettingsMenu()
{
}

void MainWindow::addViewMenu()
{
}

void MainWindow::addHelpMenu()
{
  QMenu *menu;

  menuBar()->addSeparator();

  menu = menuBar()->addMenu(_("&Help"));
  menu->addAction(standardAction(HelpContents));
  //menu->addAction(standardAction(HelpIndex));    // into prefs.
  //menu->addAction(standardAction(HelpSearch));
  menu->addSeparator();
  menu->addAction(standardAction(GoToHomepage));
  menu->addAction(standardAction(HelpForum));
  menu->addAction(standardAction(ReportBug));
  menu->addSeparator();
  menu->addAction(standardAction(AboutApp));
  menu->addAction(standardAction(AboutQt));
}

void MainWindow::setDefaultWindowSize(unsigned int width, unsigned int height)
{
  m_default_width  = width;
  m_default_height = height;
}

void MainWindow::setCentralLayout(QLayout *layout)
{
  if (! layout) {
    qWarning() << "MainWindow::setCentralLayout: layout was zero.";
    return;
  }

  QWidget *w = new QWidget;
  setCentralWidget(w);
  w->setLayout(layout);
}

void MainWindow::standardActionAboutApp()
{
  OEG::Qt::Application::runComponent("about-dialog", QStringList() << applicationBaseName());
}

void MainWindow::standardActionConnectToggle()
{
}

void MainWindow::standardActionCopy()
{
}

void MainWindow::standardActionClear()
{
}

void MainWindow::standardActionClose()
{
}

void MainWindow::standardActionCut()
{
}

void MainWindow::standardActionDelete()
{
}

void MainWindow::standardActionEdit()
{
}

void MainWindow::standardActionHelpContents()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "contents" << applicationBaseName());
}

void MainWindow::standardActionHelpIndex()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "index" << applicationBaseName());
}

void MainWindow::standardActionHelpSearch()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "search" << applicationBaseName());
}

void MainWindow::standardActionOpen()
{
}

void MainWindow::standardActionNew()
{
}

void MainWindow::standardActionPaste()
{
}

void MainWindow::standardActionPreferences()
{
}

void MainWindow::standardActionPrint()
{
}

void MainWindow::standardActionPrintPreview()
{
}

void MainWindow::standardActionPrintSettings()
{
}

void MainWindow::standardActionRedo()
{
}

void MainWindow::standardActionReload()
{
}

void MainWindow::standardActionReportBug()
{
  OEG::Qt::Application::runComponent("bug-reporter", QStringList() << qApp->applicationName());
}

void MainWindow::standardActionSave()
{
}

void MainWindow::standardActionSaveAs()
{
}

void MainWindow::standardActionUndo()
{
}

void MainWindow::standardActionZoomFitWidth()
{
}

void MainWindow::standardActionZoomFitWindow()
{
}

void MainWindow::standardActionZoomIn()
{
}

void MainWindow::standardActionZoomOut()
{
}

void MainWindow::standardActionZoomNormal()
{
}

QString MainWindow::applicationBaseName() const
{
  return dynamic_cast<OEG::Qt::Application *>(qApp)->baseName();
}

