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

#include <QtCore>
#include <QtGui>

#include <OEG/Common.h>
#include <OEG/Qt/Application.h>
#include <OEG/Qt/MessageBox.h>

#include "PropertiesDock.h"
#include "Cell.h"

PropertiesDock::PropertiesDock(QWidget *parent /*=0*/)
 : QDockWidget(_("Properties"), parent)
{
  setContentType(Cell);
  m_loading = false;

  standardValues();

  setFeatures(QDockWidget::AllDockWidgetFeatures);
  setAllowedAreas(Qt::AllDockWidgetAreas);
  m_table = new QTableWidget(11, 3, this);
  setWidget(m_table);

  m_table->setShowGrid(true);
  m_table->setGridStyle(Qt::SolidLine);
  m_table->setAlternatingRowColors(false);
  m_table->verticalHeader()->hide();
  m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_table->setSelectionMode(QAbstractItemView::SingleSelection);

  QStringList headerLabels;
  headerLabels << "" << _("Name") << _("Value");
  m_table->setHorizontalHeaderLabels(headerLabels);
  //m_table->setVerticalHeaderItem(0, new QTableWidgetItem());
  m_table->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
  m_table->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
  m_table->setColumnWidth(0, 30);

  resize(80, 200);

  QTableWidgetItem *item;
  unsigned int row = 0;

  // Colors: http://doc.trolltech.com/4.2/qt.html#GlobalColor-enum
  addGroup(_("Colors:"), Qt::yellow, row++, 2);

  item = itemAt(row, 0);
  item->setText("");
  item = itemAt(row, 1);
  item->setToolTip(_("Edit foreground color."));
  item->setText(_("Text:"));
  item = itemAt(row, 2);
  item->setText("black");
  row++;

  item = itemAt(row, 1);
  item->setToolTip(_("Edit background color."));
  item->setText(_("Background:"));
  item = itemAt(row, 2);
  item->setText("white");
  row++;

  addGroup(_("Font:"), Qt::cyan, row++, 2);

  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Font Name:"));
  item = itemAt(row, 2);
  item->setText("Arial");
  row++;

  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Font Size:"));
  item = itemAt(row, 2);
  item->setText("12");
  row++;

  addGroup(_("Margins:"), Qt::green, row++, 4);

  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Left:"));
  item = itemAt(row, 2);
  item->setText("5");
  row++;
  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Top:"));
  item = itemAt(row, 2);
  item->setText("5");
  row++;
  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Right:"));
  item = itemAt(row, 2);
  item->setText("5");
  row++;
  item = itemAt(row, 1);
  item->setToolTip("");
  item->setText(_("Bottom:"));
  item = itemAt(row, 2);
  item->setText("5");
  row++;

  m_table->resizeColumnsToContents();

  connect(m_table, SIGNAL(cellChanged(int, int)),
          this,    SLOT(tableCellChanged(int, int)));
}

PropertiesDock::~PropertiesDock()
{
}

void PropertiesDock::setContentType(ContentType type)
{
  m_content_type = type;

  if (type == Table) {

  }
  else if (type == Cell) {

  }
}

void PropertiesDock::addGroup(const QString &name, const QColor &color, const int row, const int rows)
{
  QFont groupFont("Arial", 10, QFont::Bold);
  QTableWidgetItem *item;

  m_table->setSpan(row, 0, 1, 3);
  item = itemAt(row, 0);
  item->setFont(groupFont);
  item->setBackground(color);
  item->setToolTip("");
  item->setText(name);

  m_table->setSpan(row+1, 0, rows, 1);
  item = itemAt(row+1, 0);
  item->setBackground(color);
  item = itemAt(row+2, 0);
  item->setBackground(color);
}

void PropertiesDock::standardValues()
{
  m_color_text       = QColor(0,     0,   0);
  m_color_background = QColor(255, 255, 255);
  m_title            = "";
  m_read_only        = false;
}

void PropertiesDock::loadItemValues(QTableWidgetItem *item)
{
  QTableWidgetItem *i;

  if (! item) {
    OEG::Qt::MessageBox::WarnMessage(_("PropertiesDock::loadItemValues(): No item!"));
    return;
  }

  m_loading = true;

  i = itemAt(4, 2);
  i->setText(item->font().family());
  i = itemAt(5, 2);
  i->setText(QString::number(item->font().pointSize()));

  m_item = item;

  m_loading = false;
}

void PropertiesDock::tableCellChanged(int row, int column)
{
  // m_loading is used to indicate, that the loadItemValues() slot is currently writing data into the table.
  // This results in fired tableCellChanged() slots. We have to ignore these, because the data is not
  // complete and valid. After loading the m_loading will be set to false again and then we react to
  // this slot.

  if (m_loading)
    return;

  if (! m_item) {
    OEG::Qt::MessageBox::WarnMessage(_("PropertiesDock::tableCellChanged(): No item!"));
    return;
  }

  QString str = itemAt(row, column)->text();
  OEG::Qt::MessageBox::WarnMessage(str);

  if (column == 2) {
    switch (row) {
      case 4:
        m_item->setFont(QFont(str, m_item->font().pointSize()));
        break;
      case 5:
        m_item->setFont(QFont(m_item->font().family(), str.toInt()));
        break;
      default:
        break;
    }
  }
}

QTableWidgetItem *PropertiesDock::itemAt(unsigned int row, unsigned int column)
{
  if (! m_table)
    qDebug() << "PropertiesDock::itemAt() Error: No table.";

  QTableWidgetItem *item = m_table->item(row, column);
  if (! item) {
    item = new QTableWidgetItem;

    item->setForeground(Qt::black);
    item->setBackground(Qt::white);

    //item->setFont(QFont("Arial", 10));

    if (column == 0) {
      item->setFlags(0);
    }
    else if (column == 1) {
      item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
    }
    else {
      item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    m_table->setItem(row, column, item);
  }

  return item;
}

