// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QDockWidget>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QFileSystemModel>
#include <QVBoxLayout>

#include <QDebug>

#include <OEG/Qt/MessageBox.h>
#include <OEG/Qt/TabWidget.h>

#include "ButtonsDockWidget.h"
#include "FileSystemModel.h"
#include "FolderView.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setObjectName("MainWindow");
  setWindowIcon(QIcon("icon.png"));
  setWindowTitle(_("File Manager"));

  m_tabs = new OEG::Qt::TabWidget(this);
  m_tabs->setMinimumSize(400, 200);
  m_tabs->separateCloseTabButton(_("Close this tab."));
  setCentralWidget(m_tabs);

  FolderView *view;
  view = new FolderView(0, QDir::currentPath());
  m_tabs->addTab(view, view->tabTitleForFolder());
  connect(view, SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(viewCurrentChanged(const QModelIndex &, const QModelIndex &)));

  view = new FolderView(0, "C:\\");
  m_tabs->addTab(view, view->tabTitleForFolder());
  connect(view, SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(viewCurrentChanged(const QModelIndex &, const QModelIndex &)));

  view = new FolderView(0, "I:\\");
  m_tabs->addTab(view, view->tabTitleForFolder());
  connect(view, SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(viewCurrentChanged(const QModelIndex &, const QModelIndex &)));

  m_tabs->setCurrentIndex(0);        // Before createAll()!

  createAll();

  //QTimer::singleShot(200, this, SLOT(updateFileSystemViews()));

  connect(m_dock_buttons,   SIGNAL(sendCommand(const QString &)),
          this,             SLOT(runCommand(const QString &)));

  connect(m_dock_tree_view, SIGNAL(activated(const QModelIndex &)),            // Activated, e.g. by keyboard.
          this,             SLOT(treeActivated(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(clicked(const QModelIndex &)),              // Item clicked.
          this,             SLOT(treeActivated(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(collapsed(const QModelIndex &)),
          this,             SLOT(treeCollapsed(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(expanded(const QModelIndex &)),
          this,             SLOT(treeExpanded(const QModelIndex &)));

  connect(m_tabs,           SIGNAL(currentChanged(int)),
          this,             SLOT(tabCurrentChanged(int)));
  connect(m_tabs,           SIGNAL(tabCloseRequested(int)),
          this,             SLOT(tabCloseRequested(int)));
}

MainWindow::~MainWindow()
{
  //while (! m_fs_models.isEmpty()) { // TODO
  //  if (m_fs_models.at
  //    delete m_fs_models.takeFirst();
  //}
}

void MainWindow::updateFileSystemViews()
{
  // This method does not work if it is called after creating the
  // widget or expanding a larger directory because the items are
  // inserted from a parallel thread and you have to wait until
  // it finishes. Else no items are visible and the layout is
  // badly sized (to small column because no contents).
  // Solution: Call this from a timer or after a GUI interaction.

  //qDebug() << "UPDATE FSV: can fetch more = " << dynamic_cast<QFileSystemModel *>(m_dock_tree_view->model())->canFetchMore();

  m_dock_tree_view->resizeColumnToContents(0);

}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = menuBar()->addMenu(_("&File"));

  menu->addAction(_("Update contents"), this, SLOT(updateFileSystemViews()));
  menu->addSeparator();

  action = menu->addAction(_("Load ..."));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(loadXXX()));
  action = menu->addAction(_("Save ..."));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(saveXXX()));
  menu->addSeparator();

  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createDockWidgets()
{
  m_dock_buttons = new ButtonsDockWidget(_("Buttons"), this);
  addDockWidget(Qt::BottomDockWidgetArea, m_dock_buttons);

  m_dock_tree = new QDockWidget(_("Directory Tree"), this);
  m_dock_tree_view = new QTreeView(m_dock_tree);
  m_dock_tree_view->header()->hide();
  m_dock_tree_view->setAnimated(false);
  m_dock_tree_view->setSortingEnabled(false);
  m_dock_tree_view->setIndentation(20);
  m_dock_tree_view->setAutoExpandDelay(1);
  m_dock_tree_view->setUniformRowHeights(true);
  m_dock_tree_view->setModel(currentFolderView()->fileSystemModel());
  m_dock_tree_view->setSortingEnabled(true);
  m_dock_tree_view->resizeColumnToContents(0);  // Does not work.
  m_dock_tree->setWidget(m_dock_tree_view);
  addDockWidget(Qt::LeftDockWidgetArea, m_dock_tree);
  removeColumnsFromTree();

  m_dock_preview = new QDockWidget(_("Preview"), this);
  m_dock_preview->setWidget(new QLabel("Preview", this));
  addDockWidget(Qt::RightDockWidgetArea, m_dock_preview);
}

FolderView *MainWindow::currentFolderView()
{
  return dynamic_cast<FolderView *>(m_tabs->currentWidget());
}

// Called after clicking a button from the dock. The parameter is
// the internal command name (e.g. "copy") for the button's command.

void MainWindow::runCommand(const QString &name)
{
  FolderView *fv = 0;

  qDebug() << "RC CLICKED: " << name;

  if (name == "select-all") {
    fv = currentFolderView();
    if (fv) {
      
    }
  } else if (name == "select-none") {


  } else if (name == "invert-selection") {


  }
}

void MainWindow::viewCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
  FolderView *fv = currentFolderView();
  if (fv) {                                                          // Preview files, update statistics.
    
  }
}

#include <QItemSelectionModel>
//better?
//void QItemSelectionModel::selectionChanged ( const QItemSelection & selected, const QItemSelection &deselected) [signal]

void MainWindow::treeActivated(const QModelIndex &index)
{
  m_dock_tree_view->selectionModel()->selectedRows();

  qDebug() << "treeActivated" << index;

  updateFileSystemViews();

  FolderView *fv = currentFolderView();
  if (fv) {
    fv->setRootIndex(index);
    m_tabs->setTabText(m_tabs->currentIndex(), fv->tabTitleForFolder());
  }
}

void MainWindow::treeCollapsed(const QModelIndex &index)
{
  qDebug() << "treeCollapsed";

  updateFileSystemViews();
}

void MainWindow::treeExpanded(const QModelIndex &index)
{
  qDebug() << "treeExpanded";
}

void MainWindow::directoryLoaded(const QString &path)
{
  statusBar()->showMessage(_("Directory retrieved."));
}

void MainWindow::tabCurrentChanged(int index)
{
  qDebug() << "tabCurrentChanged" << index;
}

void MainWindow::tabCloseRequested(int index)
{
  qDebug() << "tabCloseRequested" << index;
}

// The tree view has the following columns: Name, Size, Type, Date Modified.
// It is possible that columns occur after certain actions (e.g. Date Modified
// not before expanding some paths). The column count depends on the model.
// We first hide all columns and then show the first one.

void MainWindow::removeColumnsFromTree()
{
  int columns = currentFolderView()->fileSystemModel()->columnCount();

  m_dock_tree_view->showColumn(0);
  for (int i=1; i<columns; i++)
    m_dock_tree_view->hideColumn(i);
}

