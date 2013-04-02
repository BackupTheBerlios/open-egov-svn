// $Id:$
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

#include <OEG/Qt/TabbedMenuBarTab.h>

using namespace OEG::Qt;
using namespace Qt;

TabbedMenuBarTab::TabbedMenuBarTab(QObject *parent /*=0*/)
 : QObject(parent)
{
}

TabbedMenuBarTab::~TabbedMenuBarTab()
{
  removeAllGroups();
}

TabbedMenuBarGroup *TabbedMenuBarTab::group(const QString &title)
{
  if (title.length() <= 0)
    return 0;

  for (int i=0; i<m_groups.size(); i++) {
    if (m_groups.at(i)->title() == title) {
      return m_groups.at(i);
    }
  }

  TabbedMenuBarGroup *g = new TabbedMenuBarGroup(this);
  if (! g)
    return 0;

  g->setTitle(title);

  m_groups.append(g);

  return g;
}

void TabbedMenuBarTab::removeGroup(TabbedMenuBarGroup *group)
{
}

void TabbedMenuBarTab::removeAllGroups()
{
  if (m_groups.count() > 0) {
    while (! m_groups.isEmpty())
      delete m_groups.takeFirst();
  }
}

