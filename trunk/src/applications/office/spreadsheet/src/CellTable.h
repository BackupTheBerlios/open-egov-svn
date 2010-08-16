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

#include <OEG/Qt/Application.h>

#ifndef SPREADSHEET_CELLTABLE_H
#define SPREADSHEET_CELLTABLE_H

#include <QTableWidget>

class Cell;
class QIODevice;

class CellTable : public QTableWidget
{
  Q_OBJECT

  public:
    CellTable(QWidget *parent = 0);
    virtual ~CellTable();

    bool read(QIODevice *device);
    bool write(QIODevice *device);

  protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

  protected slots:

  private:
    QString  m_title;
};

#endif

