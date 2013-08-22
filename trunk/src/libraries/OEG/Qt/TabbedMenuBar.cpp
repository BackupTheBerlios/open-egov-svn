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

#include <OEG/Qt/TabbedMenuBar.h>

using namespace OEG::Qt;
using namespace Qt;

TabbedMenuBar::TabbedMenuBar(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QWidget(parent, flags)
{
  setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

  resize(200, 110);
}

TabbedMenuBar::~TabbedMenuBar()
{
  removeAllTabs();
}

TabbedMenuBarTab *TabbedMenuBar::addTab(const QString &title)
{
  TabbedMenuBarTab *tab = new TabbedMenuBarTab(this);

  //m_tabs->add(tab);

  return tab;
}

TabbedMenuBarTab *TabbedMenuBar::tab(const QString &title)
{

  return 0;
}

void TabbedMenuBar::removeTab(const QString &title)
{
}

void TabbedMenuBar::loadFromXML(const QString &fileName)
{
}

void TabbedMenuBar::removeAllTabs()
{
  if (m_tabs.count() > 0) {
    while (! m_tabs.isEmpty())
      delete m_tabs.takeFirst();
  }
}

