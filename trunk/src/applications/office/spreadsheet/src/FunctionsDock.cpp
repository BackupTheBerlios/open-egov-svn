// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <OEG/Common.h>

#include <QtCore>
#include <QtGui>

#include "FunctionsDock.h"

FunctionsDock::FunctionsDock(QWidget *parent /*=0*/)
 : QDockWidget(_("Properties"), parent)
{
  setFeatures(QDockWidget::AllDockWidgetFeatures);
  setAllowedAreas(Qt::AllDockWidgetAreas);
  m_table = new QTableWidget(5, 2, this);
  setWidget(m_table);

  m_table->setShowGrid(true);
  m_table->setGridStyle(Qt::SolidLine);
  m_table->setAlternatingRowColors(true);
  m_table->verticalHeader()->hide();

  QStringList headerLabels;
  headerLabels << _("Name") << _("Value");
  m_table->setHorizontalHeaderLabels(headerLabels);
  m_table->resizeColumnsToContents();
  //m_table->setVerticalHeaderItem(0, new QTableWidgetItem());

  // size
}

FunctionsDock::~FunctionsDock()
{
}

