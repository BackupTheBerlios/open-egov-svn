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

