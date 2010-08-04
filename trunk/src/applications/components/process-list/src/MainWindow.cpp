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
#include <OEG/Qt/ProcessList.h>
#include <OEG/Qt/ProcessInfo.h>
#include <OEG/Qt/ModuleInfo.h>
#include <OEG/Qt/ThreadInfo.h>

#include <QAction>
#include <QApplication>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QDockWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSet>
#include <QStatusBar>
#include <QTableWidget>
#include <QTime>
#include <QTimer>
#include <QToolBar>
#include <QIcon>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_table = new QTableWidget(this);
  m_table->setColumnCount(4);

  m_table->verticalHeader()->hide();
  m_table->setAlternatingRowColors(false);  // into the settings, bg colors are set!
  m_table->horizontalHeader()->setStretchLastSection(true);
  m_table->setSelectionBehavior(QAbstractItemView::SelectRows);

  //m_table->setHorizontalHeaderLabels(QStringList() << _("File Name") << _("PID") << _("PPID") << _("Path"));
  //headerItem->setIcon(QIcon(QPixmap(":/Images/test.png")));
  QTableWidgetItem *headerItem;
  headerItem = new QTableWidgetItem(_("File Name"));
  headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  m_table->setHorizontalHeaderItem(0, headerItem);
  headerItem = new QTableWidgetItem(_("PID"));
  headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  m_table->setHorizontalHeaderItem(1, headerItem);
  headerItem = new QTableWidgetItem(_("PPID"));
  headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  m_table->setHorizontalHeaderItem(2, headerItem);
  headerItem = new QTableWidgetItem(_("File Path"));
  headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  m_table->setHorizontalHeaderItem(3, headerItem);

  setCentralWidget(m_table);

  m_processes = new OEG::Qt::ProcessList(this);

  action_reload();

  m_table->resizeColumnsToContents();
  m_table->clearSelection();
  m_table->clearFocus();

  m_timer = new QTimer(this);
  m_timer->setInterval(1000 * 2); // every 2 seconds
  connect(m_timer, SIGNAL(timeout()), this, SLOT(action_reload()));
  m_timer->start();
}

MainWindow::~MainWindow()
{
  m_timer->stop();

  if (m_processes) {
    delete m_processes; m_processes = 0;
  }
}

void MainWindow::createActions()
{
  QAction *a;

  OEG::Qt::MainWindow::createActions();

  a = standardAction(Reload);
  if (a) {
    
    connect(a, SIGNAL(triggered()), this, SLOT(action_reload()));
  }

#if 0
  a = new QAction("xyz", this);
  if (! a)
    return 0;

  a->setObjectName(baseName);
  if (baseName.length() > 0)
    a->setIcon(QIcon(baseName));
  a->setShortcut(keySequence);
  a->setToolTip(info);
  a->setStatusTip(info);
#endif
}

void MainWindow::createMenus()
{
  QMenu *menu = menuBar()->addMenu(_("&File"));
  menu->addAction(standardAction(Reload));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QToolBar *toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
  toolbar->addAction(standardAction(Reload));
}

void MainWindow::createStatusBar()
{
  m_number_of_processes = new QLabel(" 000 ");
  m_number_of_processes->setMinimumSize(m_number_of_processes->sizeHint());
  m_number_of_processes->setAlignment(Qt::AlignCenter);
  m_number_of_processes->setToolTip(_("The number of processes."));
  statusBar()->addPermanentWidget(m_number_of_processes);

  m_current_time = new QLabel(" 00:00:00 ");
  m_current_time->setMinimumSize(m_current_time->sizeHint());
  m_current_time->setAlignment(Qt::AlignCenter);
  m_current_time->setToolTip(_("The current time."));
  statusBar()->addPermanentWidget(m_current_time);

  OEG::Qt::MainWindow::createStatusBar();
}

void MainWindow::action_reload()
{
  m_processes->update();
  int numP = m_processes->numberOfProcesses();
  if (numP <= 0)
    return;

  m_number_of_processes->setText(QString::number(numP));
  m_current_time->setText(QTime::currentTime().toString("hh:mm:ss"));

  QTableWidgetItem     *item;
  OEG::Qt::ProcessInfo *pi;
  OEG::Qt::ModuleInfo  *mi;
  OEG::Qt::ThreadInfo  *ti;

  m_table->setUpdatesEnabled(false);
  m_table->clearContents();
  m_table->setSortingEnabled(false);

  //if (numP != t->rowCount()) {
    m_table->setRowCount(numP);
    for (int i=0; i<numP; i++) {
      pi = m_processes->processInfo(i);
      if (pi) {
        item = new QTableWidgetItem(pi->processName());
        if (item) {
          item->setForeground(QColor(0, 0, 0));
          item->setBackground(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
          item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
          item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
          m_table->setItem(i, 0, item);
        }
        item = new QTableWidgetItem(QString::number(pi->processId()));
        if (item) {
          item->setForeground(QColor(0, 0, 0));
          item->setBackground(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
          item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
          item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
          m_table->setItem(i, 1, item);
        }
        item = new QTableWidgetItem(QString::number(pi->parentProcessId()));
        if (item) {
          item->setForeground(QColor(0, 0, 0));
          item->setBackground(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
          item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
          item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
          m_table->setItem(i, 2, item);
        }

        int numM = m_processes->numberOfModules(pi->processId());
        if (numM > 0) {
          mi = m_processes->moduleInfo(pi->processId(), 0);
          if (mi) {
            item = new QTableWidgetItem(mi->modulePath());
            if (item) {
              item->setForeground(QColor(0, 0, 0));
              item->setBackground(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
              item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
              item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
              m_table->setItem(i, 3, item);
            }
          }
        }

        int numT = m_processes->numberOfThreads(pi->processId());
        if (numT > 0) {
          ti = m_processes->threadInfo(pi->processId(), 0);
          if (ti) {
          
          }
        }

      }
    }

  m_table->setSortingEnabled(true);
  m_table->sortItems(0, Qt::AscendingOrder);
  m_table->setUpdatesEnabled(true);
}

void MainWindow::action_terminate_process()
{
  // We first get a list of the selected items. The list contains all items of the row(s).

  QList<QTableWidgetItem *> list = m_table->selectedItems();
  QSet<int> rows;
  QTableWidgetItem *item;

  if (list.size() <= 0) {
    QMessageBox::information(this, _("No selection!"),
                             _("There was no selected row. You have to select one first."), QMessageBox::Ok);
    return;
  }

  // Then the items will be traversed and their row numbers put into the rows set.
  // rows now contains a list of unique row numbers.

  for (int i=0; i<list.size(); i++) {
    item = list.at(i);
    if (item) {
      rows << item->row();
    }
  }

  // Retrieve the process name for each row number and format them for the dialog.

  QString text;
  foreach (int row, rows) {
    item = m_table->item(row, 0);    // Name.
    if (item) {
      text += item->text() + " ";
    }
    item = m_table->item(row, 1);    // PID.
    if (item) {
      text += QString("(%1)<br>").arg(item->text());
    }
  }
  text = text.trimmed();

  QMessageBox mb(this);
  mb.setWindowTitle(qApp->applicationName());
  mb.setIcon(QMessageBox::Question);
  if (list.size() == 1)
    mb.setText(_("Delete this process?"));
  else
    mb.setText(_("Delete these processes?"));
  mb.setInformativeText(text);
  mb.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  mb.setDefaultButton(QMessageBox::No);
  if (mb.exec() == QMessageBox::No)
    return;

  // Fetch the PID for every row and kill the process.

  foreach (int row, rows) {
    item = m_table->item(row, 1);
    if (item) {
      m_processes->killProcess(item->text().toInt());
    }
  }

  action_reload();
}

void MainWindow::action_open_process_dialog()
{
}

void MainWindow::action_copy_details()
{
  if (m_last_item_clicked) {
    qApp->clipboard()->setText(m_last_item_clicked->text());
    m_last_item_clicked = 0;
  }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu *menu = new QMenu(this);
  Q_CHECK_PTR(menu);
  if (! menu)
    return;

  QTableWidgetItem *item = m_table->itemAt(m_table->viewport()->mapFromGlobal(event->globalPos()));
  if (! item)
    return;

  m_last_item_clicked = item;  // Store, to allow a text copy without having the coordinates.
  //item->setBackground(QBrush(QColor(255, 0, 255)));

  bool timer_was_active = m_timer->isActive();             // Switch off auto-updates of the list.
  m_timer->stop();

  menu->addAction("&Terminate process ...", this, SLOT(action_terminate_process()), QKeySequence(_("Del")));
  menu->addSeparator();
  menu->addAction("&Copy",                  this, SLOT(action_copy_details()),      QKeySequence(_("Ctrl+C")));

  menu->exec(event->globalPos());
  delete menu; menu = 0;

  if (timer_was_active)
    m_timer->start();
}

