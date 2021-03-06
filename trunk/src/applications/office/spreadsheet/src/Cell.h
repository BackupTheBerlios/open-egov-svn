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

#pragma once

#include <OEG/Qt/Application.h>

#include <QTableWidgetItem>
#include <QString>
#include <QVariant>

#include "CellProperties.h"

class QFont;

class Cell : public QTableWidgetItem
{
  public:
    Cell();
    Cell(const QString &text);
    virtual ~Cell();

    virtual Cell *clone () const;

    QVariant data(int role) const;
    void setData(int role, const QVariant &value);

    void setReadOnly(const bool value);

    virtual void read(QDataStream &in);
    virtual void write(QDataStream &out) const;

  private:
    QString   m_text;
    QString   m_value;
    QDateTime m_datetime;
    QString   m_tooltip;
    bool      m_read_only;

    CellProperties m_properties;
};

