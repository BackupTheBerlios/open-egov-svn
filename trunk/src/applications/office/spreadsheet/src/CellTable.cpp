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
#include <OEG/Qt/Application.h>
#include <OEG/Qt/MessageBox.h>

#include <QtCore>
#include <QtGui>

#include "Cell.h"
#include "CellTable.h"
#include "CellTableView.h"

CellTable::CellTable(QWidget *parent /*=0*/)
 : QTableWidget(15, 40, parent) // rows, cols
{
  for (int c = 0; c < 40; c++) {
    setHorizontalHeaderItem(c, new QTableWidgetItem(CellTableView::encodeColumnName(c+1)));
    setColumnWidth(c, 40);
  }

  QTableWidgetItem *topLeftHeaderItem = new QTableWidgetItem(_("xy"));
  //topLeftHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
  topLeftHeaderItem->setTextAlignment(Qt::AlignVCenter);
  topLeftHeaderItem->setBackground(Qt::cyan);
  topLeftHeaderItem->setToolTip("hhh");
  topLeftHeaderItem->setText("ggg");

  //->setStyleSheet("QTableWidget  { background-color: green; } ");
//horizontalHeader()->hide()
//verticalHeader()->hide()

#if 0
void QTableView::resizeColumnToContents ( int column )
void QTableView::resizeColumnsToContents ()
void QTableView::resizeRowToContents ( int row )
void QTableView::resizeRowsToContents ()
deineTabelle->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch); 

void QHeaderView::resizeSection ( int logicalIndex, int size )

QHeaderView* header = new QHeaderView(Qt::Horizontal, tableWidget);
   header->setToolTip("Header");
   header->setClickable(true);
   header->setSortIndicatorShown(true);
   tableWidget->setHorizontalHeader(header);
   tableWidget->setColumnCount(11);
   tableWidget->setHorizontalHeaderLabels(labels);
   tableWidget->setSortingEnabled(true);
   header->setResizeMode(QHeaderView::Interactive);
   header->setResizeMode(1, QHeaderView::Stretch);
   header->resizeSection(0,23);
   header->resizeSection(1,210);
   header->resizeSection(2,60);
   header->resizeSection(3,60);

Die einzelnen Sektionen sind unterschiedlich und nur die 2. sized mit, wenn sich die Größe ändert.

ui.treeWidget->setColumnCount(4);
QStringList headers;
headers << tr("Subject") << tr("Default") << tr("Default") << tr("Default");
ui.treeWidget->setHeaderLabels(headers);
#endif

  //setItem(0, 0, topLeftHeaderItem);
  //setHorizontalHeaderItem(0, topLeftHeaderItem);

  QLabel *label = new QLabel(this);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("°");
  label->setToolTip("LABEL");
  label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  label->resize(20, 20);
  label->show();
  setCornerWidget(label);

  Cell *cellPrototype = new Cell();              // Our QTableWidgetItem subclass.

  cellPrototype->setReadOnly(false);

  setItemPrototype(cellPrototype);
}

CellTable::~CellTable()
{
}

bool CellTable::read(QIODevice *device)
{
  int row, column;

  for (row=0; row<rowCount(); row++) {
    for (column=0; column<columnCount(); column++) {
      qWarning() << "row: " << row << " column: " << column;

    }
  }

  return false;
}

bool CellTable::write(QIODevice *device)
{
  int row, column;

  for (row=0; row<rowCount(); row++) {
    for (column=0; column<columnCount(); column++) {
      qWarning() << "row: " << row << " column: " << column;

    }
  }

  return false;
}

void CellTable::contextMenuEvent(QContextMenuEvent *event)
{
  QTableWidget::contextMenuEvent(event);

}

