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
#include <QFileInfo>
#include <QHeaderView>
#include <QStatusBar>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

#include <QDebug>

#include "FolderView.h"
#include "FolderManager.h"
#include "FileSystemModel.h"
#include "MainWindow.h"

FolderView::FolderView(QWidget *parent /*=0*/)
 : QTableView(parent)
{
  setObjectName("FolderView");

  //FileSystemModel *fsm = new FileSystemModel();
  //fsm->setRootPath(path);
  //fsm->setReadOnly(false);
  //fsm->setSorting( QDir::DirsFirst | QDir::IgnoreCase );
  //setModel(fsm);

  setSortingEnabled(false);
  setShowGrid(false);
  setWordWrap(false);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);

  verticalHeader()->hide();
  horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
  horizontalHeader()->setSortIndicatorShown(true);
  horizontalHeader()->setClickable(true);

  connect(this, SIGNAL(doubleClicked(const QModelIndex &)),
          this, SLOT(doubleClicked(const QModelIndex &)));
  connect(this, SIGNAL(directoryLoaded(const QString &)),
          this, SLOT(directoryLoaded(const QString &)));
}

FolderView::~FolderView()
{
}

// Sets only the path which a FolderView shall
// display. Needed to handle the delayed retrieving
// of information and to speed up e.g. the sorting.

void FolderView::setPath(const QString &path /*=""*/)
{
  QString directory = path;
  if (directory.length() <= 0)
    directory = QDir::currentPath();

  // check model type here!!
  fileSystemModel()->setRootPath(directory);

  setRootIndex(fileSystemModel()->index(directory));
}

// Sets the directory to be displayed by an already
// existing FolderView. Handles file selections such
// as preview, execute, ... too.

void FolderView::navigateToPath(const QString &path)
{
  qDebug() << "FolderView::navigateToPath:" << path;

  QFileInfo info(path);

  if (! info.exists()) {
    qDebug() << "path doesn't exists.";
    return;
  }

  if (info.isDir()) {
    qDebug() << "is a directory";

    setPath(path);
    //scrollTo(fileSystemModel()->index(path));

    //OEG::Qt::TabWidget *tab = qobject_cast<OEG::Qt::TabWidget *>(parent());

    FolderManager *fm = folderManager();
    if (! fm) {
      qDebug() << "No fm";
      return;
    }

    OEG::Qt::TabWidget *tabs = fm->currentTabWidget();
    if (! tabs) {
      qDebug() << "No tabs"; // TODO
      return;
    }
    else {
      int index = tabs->currentIndex();
      if (index >= 0) {
        qDebug() << "New tab title:" << path;
        tabs->setTabText(index, path);
      }
    }

    return;
  }

  if (info.isFile()) {
    qDebug() << "is a file";

    if (info.completeSuffix() == "exe") {
      launchProcess(info.absoluteFilePath());
    }

    return;
  }
}

void FolderView::activateView(const bool activate /*=true*/)
{
  qDebug() << "FolderView::activateView" << activate;

  if (activate) {
    horizontalHeader()->setStyleSheet("QHeaderView { background-color: yellow; }"
                                      "QHeaderView::section { background-color: yellow; }");
  }
  else {
    horizontalHeader()->setStyleSheet("QHeaderView { /*background-color: blue;*/ }"
                                      "QHeaderView::section { background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);"
                                      "color: white;"
                                      "padding-left: 4px;"
                                      "border: 1px solid #6c6c6c; } "
                                      "QHeaderView::section:checked { background-color: red; }");
  }
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

  //model->setReadOnly(false);
  //model->setFilter(QDir::Drives | QDir::AllDirs | QDir::NoDotAndDotDot);

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

QFileSystemModel *FolderView::fileSystemModel()
{
  return dynamic_cast<QFileSystemModel *>(model());
}

QString FolderView::tabTitleForFolder()
{
  return fileSystemModel()->rootPath();
}

// Launch process.

void FolderView::launchProcess(const QString &path)
{
  QObject::connect(&m_process, SIGNAL(error(QProcess::ProcessError)),
                   this,       SLOT(processError(QProcess::ProcessError)),
                   Qt::UniqueConnection);

  m_process.startDetached(path);
}

// Look for errors.

void FolderView::processError(QProcess::ProcessError errorcode)
{
  switch(errorcode) {
    case QProcess::FailedToStart:
      QMessageBox::information(0, "FailedToStart", "FailedToStart");
      break;
    case QProcess::Crashed:
      QMessageBox::information(0, "Crashed", "Crashed");
      break;
    case QProcess::Timedout:
      QMessageBox::information(0, "FailedToStart", "FailedToStart");
      break;
    case QProcess::WriteError:
      QMessageBox::information(0, "Timedout", "Timedout");
      break;
    case QProcess::ReadError:
      QMessageBox::information(0, "ReadError", "ReadError");
      break;
    case QProcess::UnknownError:
      QMessageBox::information(0, "UnknownError", "UnknownError");
      break;
    default:
      QMessageBox::information(0, "default", "default");
      break;
  }
}

void FolderView::handleDoubleClickedFile(const QString &path)
{
  QDesktopServices::openUrl(QUrl(path));
}

void FolderView::setFolderManager(FolderManager *fm)
{
  m_folder_manager = fm;
}

FolderManager *FolderView::folderManager() const
{
  return m_folder_manager;
}

