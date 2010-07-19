// $Id$

#include <OEG/Common.h>
#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/ToolProvider.h>

#include <QAction>
#include <QApplication>
#include <QKeySequence>
#include <QList>
#include <QStatusBar>

using namespace OEG::Qt;
using namespace Qt;

MainWindow::MainWindow(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QMainWindow(parent, flags)
{
  setWindowTitle(qApp->applicationName());
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
  addStandardAction("quit", _("&Quit"), _("Exits the application and closes all windows."), _("Alt+F4"));

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
                                       const QString &info, const QString &keySequence)
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

  return 0;
}

