// $Id$
//
// Spreadsheet
// Copyright (C) 2006-2007 by Gerrit M. Albrecht
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include <QtCore>
#include <QtGui>

#include "Cell.h"

Cell::Cell()
 : QTableWidgetItem()
{
}

Cell::Cell(const QString &text)
 : QTableWidgetItem(text)
{
}

Cell::~Cell()
{
}

Cell *Cell::clone () const
{
  Cell *c = new Cell();

  c->setReadOnly(m_read_only);

  return c;
}

QVariant Cell::data(int role) const
{
  switch (role) {
    case Qt::UserRole:
      break;

    default:
      break;
  }

  return QTableWidgetItem::data(role);
}

void Cell::setData(int role, const QVariant &value)
{
  QTableWidgetItem::setData(role, value);

  if (tableWidget())
    tableWidget()->viewport()->update();

  switch (role) {
    case Qt::UserRole:
      break;

    default:
      break;
  }
}

void Cell::setReadOnly(const bool value)
{
  m_read_only = value;
}

void Cell::read(QDataStream &in)
{
  in >> m_read_only;
}

void Cell::write(QDataStream &out) const
{
  out << m_read_only;
}

