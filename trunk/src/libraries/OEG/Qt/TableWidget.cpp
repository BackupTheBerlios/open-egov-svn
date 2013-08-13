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

#include <OEG/Qt/TableWidget.h>

#include <QFontMetrics>
#include <QHeaderView>

using namespace OEG::Qt;
using namespace Qt;

TableWidget::TableWidget(QWidget *parent /*=0*/)
 : QTableWidget(parent)
{
}

TableWidget::~TableWidget()
{
}

int TableWidget::maximumColumnWidth(const int column) const
{
  QFontMetrics fm(font());
  int maxColumnWidth = 0;

  for (int row=0 ; row<rowCount(); row++) {
    int currentTextWidth = fm.width(item(row, column)->text());

    if (maxColumnWidth < currentTextWidth)
      maxColumnWidth = currentTextWidth;
  }

  int headerWidth = horizontalHeader()->sectionSize(column);
  if (maxColumnWidth < headerWidth)
    maxColumnWidth = headerWidth;

  return maxColumnWidth;
}

void TableWidget::resizeColumnToMaximumContents(const int column)
{
  int maxColumnWidth = maximumColumnWidth(column);

  horizontalHeader()->setSectionResizeMode(column, QHeaderView::Fixed);
  setColumnWidth(column, maxColumnWidth * 1.1);
}

