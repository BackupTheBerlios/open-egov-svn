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

#pragma once

#include <QObject>
#include <QStringList>
#include <QDebug>

class Column : public QObject
{
  public:
    enum Datatype {         // http://www.w3schools.com/SQl/sql_datatypes.asp
      Text,                 // 255 characters text.
      Memo,                 // 65,536 characters text. Not sortable, but searchable.
      Byte,                 // Numbers from 0 to 255 (1 byte).
      Integer,              // Numbers from -32,768 to 32,767 (2 bytes).
      Long,                 // Numbers from -2,147,483,648 to 2,147,483,647 (4 bytes).
      Single,               // Single precision floating-point value (4 bytes).
      Double,               // Double precision floating-point value (8 bytes).
      AutoNumber,           // Each record gets its own number automatically starting at 1 (4 bytes).
      DateTime,             // Holds a date or a time (8 bytes).
      VarChar,      
      YesNo,
      OptionList,
      HyperLink,
      BinaryObject,
      Currency
    };

  public:
    Column();
    virtual ~Column();

    Column *column(const QString &columnName, bool create = false);
    Column *createColumn(const QString &columnName);
    bool existsColumn(const QString &columnName);
    bool removeColumn(const QString &columnName);

    QStringList columns() const;
    QString name() const;

  protected:
    QString  m_name;
    Datatype m_datatype;
};

