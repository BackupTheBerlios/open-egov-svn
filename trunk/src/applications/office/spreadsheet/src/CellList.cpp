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

#include "CellList.h"
#include "Cell.h"

CellList::CellList()
{
}

CellList::~CellList()
{
  while (! m_list.isEmpty())
    delete m_list.takeFirst();
}

void CellList::append(const Cell *address)
{
  if (address)
    m_list.append(const_cast<Cell *>(address));
}

Cell *CellList::at(unsigned int i) const
{
  return m_list.at(i);
}

unsigned int CellList::count() const
{
  return m_list.count();
}

