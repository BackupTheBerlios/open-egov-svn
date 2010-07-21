// $Id$

#include "MainWindow.h"

#include <OEG/Qt/ToolProvider.h>
#include <OEG/Qt/ProcessList.h>
#include <OEG/Qt/ProcessInfo.h>
#include <OEG/Qt/ModuleInfo.h>
#include <OEG/Qt/ThreadInfo.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QTableWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  QTableWidget *table = new QTableWidget(this);
  table->setColumnCount(4);
  table->setHorizontalHeaderLabels(QStringList() << _("File Name") << _("PID") << _("PPID") << _("Path"));
  table->verticalHeader()->hide();
  table->setAlternatingRowColors(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);

  setCentralWidget(table);

  m_processes = new OEG::Qt::ProcessList(this);
  m_processes->update();
  int numP = m_processes->numberOfProcesses();
  if (numP <= 0)
    return;

  QTableWidgetItem *item;
  OEG::Qt::ProcessInfo *pi;
  OEG::Qt::ModuleInfo  *mi;
  OEG::Qt::ThreadInfo  *ti;

  table->clearContents();
  table->setSortingEnabled(false);

  //if (numP != t->rowCount()) {
    table->setRowCount(numP);
    for (int i=0; i<numP; i++) {
      pi = m_processes->processInfo(i);
      if (pi) {
        item = new QTableWidgetItem(pi->processName());
        if (item)
          table->setItem(i, 0, item);
        item = new QTableWidgetItem(QString::number(pi->processId()));
        if (item)
          table->setItem(i, 1, item);
        item = new QTableWidgetItem(QString::number(pi->parentProcessId()));
        if (item)
          table->setItem(i, 2, item);

        int numM = m_processes->numberOfModules(pi->processId());
        if (numM > 0) {
          mi = m_processes->moduleInfo(pi->processId(), 0);
          if (mi) {
            item = new QTableWidgetItem(mi->modulePath());
            if (item)
              table->setItem(i, 3, item);
          }
        }

        int numT = m_processes->numberOfThreads(pi->processId());
        if (numT > 0) {
          ti = m_processes->threadInfo(pi->processId(), 0);
          if (mi) {
          
          }
        }

      }
    }
  table->setSortingEnabled(true);
  table->sortItems(0, Qt::AscendingOrder);
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  fileMenu->addAction(standardAction("exit"));
}

void MainWindow::createToolBars()
{
  QAction  *a;
  QToolBar *t;

  t = addToolBar(_("File"));
  a = standardAction("exit");
  a->setShortcuts(QKeySequence::Quit);
  t->addAction(a);

}

void MainWindow::createDockWidgets()
{
}

