// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <OEG/Pages/PageList.h>

#include <QString>

using namespace OEG::Pages;
using namespace Qt;

PageList::PageList(QWidget *parent /*=0*/)
 : QWidget(parent)
{
  m_show_thumbnails = true;
}

PageList::~PageList()
{
}

void PageList::setShowThumbnails(const bool color)
{
  m_show_thumbnails = color;
}

bool PageList::showThumbnails() const
{
  return m_show_thumbnails;
}

