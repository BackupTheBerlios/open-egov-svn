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

#include <QDir>
#include <QString>
#include <QFile>
#include <QModelIndex>
#include <QVariant>
#include <QDebug>

#include "FileSystemModel.h"

FileSystemModel::FileSystemModel(QObject *parent /*=0*/)
 : QFileSystemModel(parent)
{
  setObjectName("FileSystemModel");

}

FileSystemModel::~FileSystemModel()
{
}

QVariant FileSystemModel::data(const QModelIndex &index, int role /*=Qt::DisplayRole*/) const
{
  //Q_UNUSED(role)

  if (! index.isValid())
    return QVariant();

  //QString xxx = list_data.at(index.row());
  //return row_data;
  if (index.column() == 1) {
    //if (index.row() == 11) {
//QVariant v = QFileSystemModel::data(index, Qt::EditRole);
//      qDebug() << index.row() << v; //<< index.data();
//return v;
    //}
  }

  return QFileSystemModel::data(index, role);
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
     QString("Column %1").arg(section);
  }

  return QFileSystemModel::headerData(section, orientation, role);
}

