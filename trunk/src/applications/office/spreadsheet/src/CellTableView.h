// $Id$
//
// Spreadsheet
// Copyright (C) 2006-2007 by Gerrit M. Albrecht
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#ifndef SPREADSHEET_CELLTABLEVIEW_H
#define SPREADSHEET_CELLTABLEVIEW_H

#include <QWidget>
#include <QString>

class CellTable;
class QTextEdit;
class QComboBox;

class CellTableView : public QWidget
{
  Q_OBJECT

  public:
    CellTableView(QWidget *parent = 0);
    virtual ~CellTableView();

    static QString encodePositionName(int row, int col);
    static void decodePositionName(const QString &pos, int *row, int *col);
    static QString encodeColumnName(int col);
    static int decodeColumnName(const QString &name);

  protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

  protected slots:

  private:
    QComboBox  *m_list;
    QTextEdit  *m_value;
    QString     m_title;
    CellTable  *m_table;
    CellTable  *m_view_1;
    CellTable  *m_view_2;
    CellTable  *m_view_3;
    CellTable  *m_view_4;
};

#endif

