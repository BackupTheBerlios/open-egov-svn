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

#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>

#include "PartListTab.h"

PartListTab::PartListTab(QWidget *parent /*=0*/)
 : QFrame(parent)
{
  //setFrameStyle(Sunken | StyledPanel);

  m_widget = new QWidget(this);

  m_widget->show();

  QPalette pal = palette();
  pal.setColor(backgroundRole(), QColor("red"));
  setPalette(pal);
  setBackgroundRole(QPalette::Background);
  setAutoFillBackground(true);


  QHBoxLayout *layout = new QHBoxLayout;
  //layout->setContentsMargins(0, 0, 0, 0);        // Else there would be a 5px margin around the graphics view.
  layout->addWidget(m_widget);
  setLayout(layout);
}

PartListTab::~PartListTab()
{
  if (m_widget) {
    delete m_widget; m_widget = 0;
  }
}

