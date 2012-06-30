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

#include "Table.h"
#include "Column.h"

Column::Column()
{
}

Column::~Column()
{
}

Column *Column::column(const QString &columnName, bool create /*=false*/)
{
  if (create && !existsColumn(columnName))
    return createColumn(columnName);

  Column *c = new Column();
  if (! c)
    return 0;

  

  return c;
}

Column *Column::createColumn(const QString &columnName)
{
  Column *c = new Column();
  if (! c)
    return 0;

  

  return c;
}

bool Column::existsColumn(const QString &columnName)
{

  return true;
}

bool Column::removeColumn(const QString &columnName)
{

  return true;
}

QStringList Column::columns() const
{
  return QStringList();
}

QString Column::name() const
{
  return m_name;
}

