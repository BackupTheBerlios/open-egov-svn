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

#include <OEG/Qt/Application.h>

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

