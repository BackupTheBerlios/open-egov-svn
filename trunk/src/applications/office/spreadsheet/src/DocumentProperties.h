// $Id$
//
// Spreadsheet
// Copyright (C) 2005-2007 by Gerrit M. Albrecht
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

#ifndef SPREADSHEET_DOCUMENTPROPERTIES_H
#define SPREADSHEET_DOCUMENTPROPERTIES_H

#include <GASI/Common.h>

#include <QObject>
#include <QDateTime>
#include <QString>

class DocumentProperties : public QObject
{
  Q_OBJECT

  public:
    DocumentProperties();

    inline QString filename() const { return m_filename; }
    inline void setFilename(const QString &filename) { m_filename = filename; }

  protected:

  private slots:

  private:
    QString   m_filename;

  public:
    QString   m_author;
    QString   m_company;
    QDateTime m_date_created;
    QDateTime m_date_changed;
};

#endif

