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

#include <QAbstractProxyModel>
#include <QHeaderView>
#include <QStatusBar>
#include <QTimer>
#include <QDebug>

#include "FolderManager.h"
#include "FolderView.h"
#include "FileSystemModel.h"
#include "MainWindow.h"

FolderManager::FolderManager(QWidget *parent /*=0*/)
 : QSplitter(parent)
{
  setObjectName("FolderManager");

  m_file_system_model = new QFileSystemModel();
  //m_file_system_model->setRootPath(path);
  m_file_system_model->setReadOnly(false);
  //m_file_system_model->setSorting(QDir::DirsFirst | QDir::IgnoreCase);
  //setModel(m_file_system_model);

  m_tabs_left = new OEG::Qt::TabWidget(this);
  m_tabs_left->setMovable(true);
  m_tabs_left->setMinimumSize(300, 200);
  m_tabs_left->separateCloseTabButton(_("Close this tab."));

  m_tabs_right = new OEG::Qt::TabWidget(this);
  m_tabs_right->setMovable(true);
  m_tabs_right->setMinimumSize(300, 200);
  m_tabs_right->separateCloseTabButton(_("Close this tab."));

  connect(m_tabs_left,    SIGNAL(currentChanged(int)),
          this,           SLOT(tabCurrentChanged(int)));
  connect(m_tabs_left,    SIGNAL(tabCloseRequested(int)),
          this,           SLOT(tabCloseRequested(int)));
  connect(m_tabs_right,   SIGNAL(currentChanged(int)),
          this,           SLOT(tabCurrentChanged(int)));
  connect(m_tabs_right,   SIGNAL(tabCloseRequested(int)),
          this,           SLOT(tabCloseRequested(int)));

  setActiveSide(LeftSide);

  addFolderTab(QDir::currentPath(), LeftSide);
  addFolderTab("C:\\", LeftSide);
  addFolderTab("I:\\", RightSide);

  m_tabs_left->setCurrentIndex(0);                         // Before createAll()!
  m_tabs_right->setCurrentIndex(0);                        // Before createAll()!

  connect(m_tabs_left,  SIGNAL(currentChanged(int)),       // Needed to set the active view.
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_right, SIGNAL(currentChanged(int)),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_left,  SIGNAL(mousePressed()),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_right, SIGNAL(mousePressed()),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_left,  SIGNAL(keyPressed()),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_right, SIGNAL(keyPressed()),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_left,  SIGNAL(tabClicked(int)),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_right, SIGNAL(tabClicked(int)),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_left,  SIGNAL(mousePressedAtTabBar()),
          this,         SLOT(tabWidgetCurrentChanged()));
  connect(m_tabs_right, SIGNAL(mousePressedAtTabBar()),
          this,         SLOT(tabWidgetCurrentChanged()));
}

FolderManager::~FolderManager()
{
}

void FolderManager::addFolderTab(const QString &path, const SideOfView side)
{
  OEG::Qt::TabWidget *tabs = (side == LeftSide) ? m_tabs_left : m_tabs_right;
  FolderView *view = new FolderView(0);

  view->setModel(m_file_system_model);
  view->setPath(path);
  view->setFolderManager(this);

  tabs->addTab(view, view->tabTitleForFolder());

  //connect(view, SIGNAL(directoryLoaded(const QString &)),
  //        this, SLOT(viewDirectoryLoaded(const QString &)));
  //connect(view, SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
  //        this, SLOT(viewCurrentChanged(const QModelIndex &, const QModelIndex &)));

  connect(view, SIGNAL(activated(const QModelIndex &)),    // Needed to set the active view.
          this, SLOT(folderViewActivated()));
}

OEG::Qt::TabWidget *FolderManager::currentTabWidget()
{
  return (m_active_side == LeftSide) ? m_tabs_left : m_tabs_right;
}

void FolderManager::addFolderTabToActiveSide(const QString &path)
{
  addFolderTab(path, m_active_side);
}

void FolderManager::setActiveSide(const SideOfView side)
{
  qDebug() << "FolderManager::setActiveViewSide()" << side;

  m_active_side = side;

  FolderView *view;

  view = currentFolderView(LeftSide);
  if (view) {
    view->activateView(m_active_side == LeftSide);
  }

  view = currentFolderView(RightSide);
  if (view) {
    view->activateView(m_active_side != LeftSide);
  }
}

// Returns the current FolderView object depending on the parameter
// activeView. If it is true, the left side's, else the right side's
// current FolderView is retrieved.

FolderView *FolderManager::currentFolderView(const SideOfView side)
{
  OEG::Qt::TabWidget *tabs = (side == LeftSide) ? m_tabs_left : m_tabs_right;

  if (tabs->currentIndex() < 0)
    return 0;

  return qobject_cast<FolderView *>(tabs->currentWidget());
}

void FolderManager::tabWidgetCurrentChanged()
{
  qDebug() << "FolderManager::tabWidgetCurrentChanged()";

  OEG::Qt::TabWidget *widget = qobject_cast<OEG::Qt::TabWidget *>(sender());

  if (widget == m_tabs_left)
    setActiveSide(LeftSide);

  if (widget == m_tabs_right)
    setActiveSide(RightSide);
}

void FolderManager::folderViewActivated()
{
  qDebug() << "FolderManager::folderViewActivated()";

  FolderView *view = qobject_cast<FolderView *>(sender());

  if (m_tabs_left->indexOf(view) >= 0)
    setActiveSide(LeftSide);

  if (m_tabs_right->indexOf(view) >= 0)
    setActiveSide(RightSide);
}

// Called after clicking a button from the dock. The parameter is
// the internal command name (e.g. "copy") for the button's command.

void FolderManager::runCommand(const QString &name)
{
  qDebug() << "FolderManager::runCommand()" << name;

  FolderView *sourceView = currentFolderView(m_active_side);
  FolderView *targetView = currentFolderView((m_active_side == LeftSide) ? RightSide : LeftSide);

  if (! sourceView) {
    qDebug() << "no source view";
    return;
  }

  if (name == "parent") {
    QDir dir(sourceView->fileSystemModel()->rootPath());
    dir.cdUp();
    sourceView->navigateToPath(dir.absolutePath());
  }
  else if (name == "select-all") {
    sourceView->selectAll();
  }
  else if (name == "select-none") {
    sourceView->clearSelection();
  }
  else if (name == "invert-selection") {
    QItemSelectionModel *selectionModel  = sourceView->selectionModel();
    selectionModel->select(selectionModel->selection(), QItemSelectionModel::Toggle);

#if 0
    QAbstractItemModel  *model        = sourceView->model();
    QModelIndex          topLeft      = model->index(0, 0);
    QModelIndex          bottomRight  = model->index(model->rowCount(parent)-1,
                                                     model->columnCount(parent)-1);
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Toggle);
#endif
  }
}

void FolderManager::tabCurrentChanged(int index)
{
  qDebug() << "FolderManager::tabCurrentChanged" << index;
}

void FolderManager::tabCloseRequested(int index)
{
  qDebug() << "FolderManager::tabCloseRequested" << index;
}

