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

#include <QtCore>
#include <QtGui>

#include "CellTableView.h"
#include "CellTable.h"

CellTableView::CellTableView(QWidget *parent /*=0*/)
 : QWidget(parent)
{
  m_table = new CellTable(this);
}

CellTableView::~CellTableView()
{
  if (m_table)
    delete m_table;
}

// TODO: Latin1 alphabet uses 26 chars - what is with e.g. arabic chars?

QString CellTableView::encodePositionName(int row, int col)
{
  return CellTableView::encodeColumnName(col) + QString::number(row);
}

void CellTableView::decodePositionName(const QString &pos, int *row, int *col)
{
  *row = 0;
  *col = 0;

  if (pos.isEmpty()) {
    qWarning() << "CellTableView::decodePositionName(): pos string is empty.";
    return;
  }

  QRegExp re;
  QString str;

  str = pos.toUpper();

  re = QRegExp("R([0-9]+)C([0-9]+)");
  if (re.exactMatch(str)) {                                // R1C1 format.
    *row = re.cap(1).toInt() - 1;
    *col = re.cap(2).toInt() - 1;

    return;
  }

  re = QRegExp("([A-Z]+)([0-9]+)");
  if (re.exactMatch(str)) {                                // A1 format.
    *row = re.cap(2).toInt() - 1;
    *col = CellTableView::decodeColumnName(re.cap(1));

    return;
  }
}

#if 0
  To Check the encode and decode routines use something like this:

#include <OEG/Qt/MessageDialog.h>

  OEG::Qt::MessageDialog::InfoMessage(QString::number(CellTableView::decodeColumnName("A")));
  OEG::Qt::MessageDialog::InfoMessage(QString::number(CellTableView::decodeColumnName("CG")));
  OEG::Qt::MessageDialog::InfoMessage(QString::number(CellTableView::decodeColumnName("AA")));
  OEG::Qt::MessageDialog::InfoMessage(QString::number(CellTableView::decodeColumnName("IV")));

  OEG::Qt::MessageDialog::InfoMessage(CellTableView::encodeColumnName(1));
  OEG::Qt::MessageDialog::InfoMessage(CellTableView::encodeColumnName(85));
  OEG::Qt::MessageDialog::InfoMessage(CellTableView::encodeColumnName(27));
  OEG::Qt::MessageDialog::InfoMessage(CellTableView::encodeColumnName(256));
#endif

QString CellTableView::encodeColumnName(int col)
{
  QString result;
  unsigned int chars = 26;
  unsigned int mod;

  if (col > 32000)
    qWarning() << "CellTableView::encodeColumnName(col): col > 32000 may cause problems.";

  while (col > 0) {
    mod = (col - 1) % chars;
    col = (col - mod) / chars;

    result = QString(mod + 'A') + result;
  }
  
  return result;
}

int CellTableView::decodeColumnName(const QString &name)
{
  int value = 0;
  int pos = name.size();
  unsigned int help  = 1;
  unsigned int chars = 26;
  QString str = name.toUpper();

  while (pos > 0) {
    value += ((str.at(--pos).toLatin1() - 'A') + 1) * help;
    help *= chars;
  }

  return value;
}

void CellTableView::contextMenuEvent(QContextMenuEvent *event)
{
  QWidget::contextMenuEvent(event);
}

