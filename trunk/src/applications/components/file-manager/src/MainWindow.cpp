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

#include <OEG/Qt/ToolProvider.h>

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QDockWidget>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QListView>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QSplitter>
#include <QTabWidget>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QItemSelectionModel>

#include <QDebug>

#include <OEG/Qt/MessageBox.h>
#include <OEG/Qt/TabWidget.h>

#include "ButtonsDockWidget.h"
#include "FileSystemModel.h"
#include "FolderManager.h"
#include "FolderView.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setObjectName("MainWindow");
  setWindowIcon(QIcon("icon.png"));
  setWindowTitle(_("File Manager"));

  m_folder_manager = new FolderManager(this);
  setCentralWidget(m_folder_manager);

  createAll();

  //QTimer::singleShot(200, this, SLOT(updateFileSystemViews()));

  connect(m_dock_buttons,   SIGNAL(sendCommand(const QString &)),
          m_folder_manager, SLOT(runCommand(const QString &)));

#if 0
  connect(m_dock_tree_view, SIGNAL(activated(const QModelIndex &)),            // Activated, e.g. by keyboard.
          this,             SLOT(treeActivated(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(clicked(const QModelIndex &)),              // Item clicked.
          this,             SLOT(treeActivated(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(doubleClicked(const QModelIndex &)),        // Item double-clicked.
          this,             SLOT(treeDoubleClicked(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(collapsed(const QModelIndex &)),
          this,             SLOT(treeCollapsed(const QModelIndex &)));
  connect(m_dock_tree_view, SIGNAL(expanded(const QModelIndex &)),
          this,             SLOT(treeExpanded(const QModelIndex &)));

  connect(m_dock_model,     SIGNAL(directoryLoaded(const QString &)),
          this,             SLOT(modelDirectoryLoaded(const QString &)));
  connect(m_dock_model,     SIGNAL(fileRenamed(const QString &,const QString &,const QString &)),
          this,             SLOT(modelFileRenamed(const QString &,const QString &,const QString &)));
  connect(m_dock_model,     SIGNAL(rootPathChanged(const QString &)),
          this,             SLOT(modelRootPathChanged(const QString &)));

  connect(m_tabs,           SIGNAL(currentChanged(int)),
          this,             SLOT(tabCurrentChanged(int)));
  connect(m_tabs,           SIGNAL(tabCloseRequested(int)),
          this,             SLOT(tabCloseRequested(int)));
#endif
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

  menu = menuBar()->addMenu(_("&Bookmarks"));
  action = menu->addAction(_("C:\\"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(newTabWithPath()));
  action = menu->addAction(_("D:\\"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(newTabWithPath()));

  menu = menuBar()->addMenu(_("&View"));
  action = menu->addAction(_("&Buttons"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(viewButtons()));
  action = menu->addAction(_("&Preview"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(viewPreview()));
  action = menu->addAction(_("&Directory Tree"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(viewDirectoryTree()));
  action = menu->addAction(_("&My Directories"));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(viewMyDirectories()));

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
  m_dock_my_dirs = new QDockWidget(_("My Directories"), this);
  m_dock_my_dirs_view = new QListView(m_dock_my_dirs);
  m_dock_my_dirs->setWidget(m_dock_my_dirs_view);
  addDockWidget(Qt::LeftDockWidgetArea, m_dock_my_dirs);

  m_dock_buttons = new ButtonsDockWidget(_("Buttons"), this);
  addDockWidget(Qt::BottomDockWidgetArea, m_dock_buttons);

  QFileSystemModel *m_dock_model = new QFileSystemModel;
  m_dock_model->setRootPath(QDir::currentPath());
  m_dock_model->setReadOnly(true);
  m_dock_model->setFilter(QDir::Drives | QDir::AllDirs | QDir::NoDotAndDotDot);

  //scrollTo(index)
  //setExpanded(index, true);
  //setRootIndex(index)
  //model->setSorting( QDir::DirsFirst | QDir::IgnoreCase );

  m_dock_tree = new QDockWidget(_("Directory Tree"), this);
  m_dock_tree_view = new QTreeView(m_dock_tree);
  m_dock_tree_view->header()->hide();
  m_dock_tree_view->setAnimated(false);
  m_dock_tree_view->setSortingEnabled(false);
  m_dock_tree_view->setIndentation(20);
  m_dock_tree_view->setAutoExpandDelay(1);
  m_dock_tree_view->setUniformRowHeights(true);
  m_dock_tree_view->setModel(m_dock_model); //currentFolderView()->fileSystemModel()
  m_dock_tree_view->setSortingEnabled(true); // LATER via SIGNAL; tree->setRootIndex(model->index(QDir::currentPath()));
  m_dock_tree_view->resizeColumnToContents(0);  // Does not work. LATER
  m_dock_tree->setWidget(m_dock_tree_view);
  addDockWidget(Qt::LeftDockWidgetArea, m_dock_tree);
  removeColumnsFromTree();

  m_dock_preview = new QDockWidget(_("Preview"), this);
  m_dock_preview->setWidget(new QLabel("Preview", this));
  addDockWidget(Qt::RightDockWidgetArea, m_dock_preview);
}

FolderView *MainWindow::currentFolderView()
{
  return 0; //dynamic_cast<FolderView *>(m_tabs_left->currentWidget());
}

void MainWindow::viewCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
  FolderView *view = currentFolderView();
  if (! view) {
    qDebug() << "MainWindow::viewCurrentChanged()" << "no view";
    return;
  }

  if (! current.isValid()) {
    qDebug() << "index not valid";
    return;
  }

  QFileSystemModel *model = view->fileSystemModel();

  qDebug() << "VCC: current"  << model->filePath(current);
  qDebug() << "VCC: previous" << model->filePath(previous);

  //view->navigateToPath(model->filePath(current));

// http://qt-project.org/doc/qt-4.8/qfilesystemmodel.html
// void 	directoryLoaded ( const QString & path )
// void 	fileRenamed ( const QString & path, const QString & oldName, const QString & newName )
// void 	rootPathChanged ( const QString & newPath )

  // Preview files, update statistics.
}

//better?
//void QItemSelectionModel::selectionChanged ( const QItemSelection & selected, const QItemSelection &deselected) [signal]

void MainWindow::treeActivated(const QModelIndex &index)
{
  m_dock_tree_view->selectionModel()->selectedRows();

  qDebug() << "MainWindow::treeActivated" << index;

  updateFileSystemViews();

  FolderView *view = currentFolderView();
  if (view) {
    view->setRootIndex(index);
    //m_tabs->setTabText(m_tabs->currentIndex(), view->tabTitleForFolder());
  }
}

void MainWindow::treeCollapsed(const QModelIndex &index)
{
  qDebug() << "MainWindow::treeCollapsed";

  updateFileSystemViews();
}

void MainWindow::treeExpanded(const QModelIndex &index)
{
  qDebug() << "MainWindow::treeExpanded";
}

void MainWindow::viewDirectoryLoaded(const QString &path)
{
  qDebug() << "MainWindow::viewDirectoryLoaded()" << path;

  statusBar()->showMessage(_("Directory retrieved."));
}

void MainWindow::tabCurrentChanged(int index)
{
  qDebug() << "MainWindow::tabCurrentChanged" << index;
}

void MainWindow::tabCloseRequested(int index)
{
  qDebug() << "MainWindow::tabCloseRequested" << index;
}

// The tree view has the following columns: Name, Size, Type, Date Modified.
// It is possible that columns occur after certain actions (e.g. Date Modified
// not before expanding some paths). The column count depends on the model.
// We hide all columns except the first one.

void MainWindow::removeColumnsFromTree()
{
  int columns = m_dock_tree_view->model()->columnCount();

  m_dock_tree_view->showColumn(0);
  for (int i=1; i<columns; i++)
    m_dock_tree_view->hideColumn(i);
}

void MainWindow::newTabWithPath()
{
  qDebug() << "MainWindow::newTabWithPath";

  QAction *action = qobject_cast<QAction *>(sender());

  m_folder_manager->addFolderTabToActiveSide(action->text());
}

