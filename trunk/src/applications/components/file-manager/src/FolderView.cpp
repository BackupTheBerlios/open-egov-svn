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

#include <QAbstractProxyModel>
#include <QFileInfo>
#include <QHeaderView>
#include <QStatusBar>
#include <QTimer>

#include <QDebug>

#include "FolderView.h"
#include "FileSystemModel.h"
#include "MainWindow.h"

FolderView::FolderView(QWidget *parent /*=0*/, const QString &path /*=""*/)
 : QTableView(parent)
{
  setObjectName("FolderView");

  FileSystemModel *fsm = new FileSystemModel();
  fsm->setRootPath(path);
  fsm->setReadOnly(false);
  //fsm->setSorting( QDir::DirsFirst | QDir::IgnoreCase );
  setModel(fsm);

  setSortingEnabled(false);
  setShowGrid(false);
  setWordWrap(false);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);

  //verticalHeader()->setClickable(true);
  //header()->setSortIndicator(0, Qt::AscendingOrder);
  //header()->setSortIndicatorShown(true);

  connect(this, SIGNAL(doubleClicked(const QModelIndex &)),
          this, SLOT(doubleClicked(const QModelIndex &)));
  connect(this, SIGNAL(directoryLoaded(const QString &)),
          this, SLOT(directoryLoaded(const QString &)));
}

FolderView::~FolderView()
{
}

void FolderView::navigateToPath(const QString &path)
{
  qDebug() << "navi to new path = " << path;

  scrollTo(fileSystemModel()->index(path));
}

void FolderView::doubleClicked(const QModelIndex &index)
{
  //qDebug() << "index" << index;
  //qDebug() << "data" << index.data();

  //QAbstractItemView::doubleClicked(index);

  if (index.column() == 0) {     // Click on a file or directory name. Offer to change it.

    qDebug() << index.row();
    selectRow(index.row());
  }
  else {

  }

  //QFileInfo fi = fsm->fileInfo(index);
  //navigateToPath(fi.absoluteFilePath());
  navigateToPath(fileSystemModel()->filePath(index));
}

void FolderView::setModel(QAbstractItemModel *model)
{
  setSortingEnabled(false);

  QTableView::setModel(model);

  setSortingEnabled(true);

  QTimer::singleShot(200, this, SLOT(resizeToContents()));
}

void FolderView::resizeToContents()
{
  resizeColumnsToContents();
  //resizeColumnToContents(0);  // Does not work.
}

//virtual void FolderView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
//  qDebug() << "SEL:" << selected.indexes().data(Qt::DisplayRole);
//  QTableView::selectionChanged(selected, deselected);

FileSystemModel *FolderView::fileSystemModel()
{
  return dynamic_cast<FileSystemModel *>(model());
}

QString FolderView::tabTitleForFolder()
{
  return fileSystemModel()->rootPath();
}

