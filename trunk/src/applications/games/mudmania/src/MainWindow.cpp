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

#include <OEG/Qt/TabWidget.h>
#include <OEG/Qt/Application.h>

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QFile>
#include <QIcon>
#include <QLabel>
#include <QMenuBar>
#include <QScriptValue>
#include <QSplitter>
#include <QStatusBar>
#include <QTextEdit>
#include <QToolBar>

#include "MainWindow.h"
#include "MultiLineEdit.h"
#include "Splitter.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  m_tabs = new OEG::Qt::TabWidget(this);
  m_tabs->addTab(new QWidget(this), _("No active game"));
  m_tabs->setTabsClosable(false);
  m_tabs->separateCloseTabButton(_("Close current tab."));

  m_input = new MultiLineEdit(this);
  m_input->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  m_input->setText(qApp->applicationName() + " " + dynamic_cast<OEG::Qt::Application *>(qApp)->applicationVersion() + "\n");
  m_input->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

  m_splitter = new Splitter(this);
  m_splitter->setOrientation(Qt::Vertical);
  m_splitter->addWidget(m_tabs);
  m_splitter->addWidget(m_input);
  m_splitter->setHandleWidth(50);
  setCentralWidget(m_splitter);

  //createAll();
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  createJavaScriptObjects();
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
  QMenu *menu;

  menu = menuBar()->addMenu(_("&File"));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QToolBar *toolbar;
  QAction  *action;

  toolbar = addToolBar(_("File"));

  action = standardAction(Exit);
  toolbar->addAction(action);
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createJavaScriptObjects()
{
  // app
  QScriptValue js_app = m_engine.newQObject(qApp);
  m_engine.globalObject().setProperty("app", js_app);

  // gui
  QScriptValue js_gui = m_engine.newQObject(0);
  m_engine.globalObject().setProperty("gui", js_gui);

  QScriptValue js_window = m_engine.newQObject(this);
  js_gui.setProperty("window", js_window);

  QScriptValue js_splitter_handle = m_engine.newQObject(dynamic_cast<QSplitter *>(m_splitter)->handle(1));
  js_gui.setProperty("splitterhandle", js_splitter_handle);

  QScriptValue js_statusbar = m_engine.newQObject(statusBar());
  js_gui.setProperty("statusbar", js_statusbar);

  // players
  //QScriptValue js_players = m_engine.newQObject(xx);
  //m_engine.globalObject().setProperty("players", js_players, QScriptValue::ReadOnly);
}

void MainWindow::runJavaScript(const QString &s)
{
  QScriptValue result = m_engine.evaluate(s);

  if (m_engine.hasUncaughtException()) {
    int line = m_engine.uncaughtExceptionLineNumber();
    qDebug() << "Uncaught exception at line" << line << ":" << result.toString();
  }
}

void MainWindow::runJavaScriptFromFile(const QString &fileName)
{
  if (fileName.length() <= 0)
    return;

  QFile file(fileName);
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QString s = "";
  QTextStream in(&file);
  while (! in.atEnd()) {                 // while (! file.atEnd()) {
    QString line = in.readLine();        //   QByteArray line = file.readLine();
    s += line;
  }

  if (s.length() <= 0)
    return;

  runJavaScript(s);
}

