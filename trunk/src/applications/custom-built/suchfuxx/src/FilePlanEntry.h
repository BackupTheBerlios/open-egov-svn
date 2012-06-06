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
#include <QString>

class FilePlanEntry : public QObject
{
  Q_OBJECT

  public:
    FilePlanEntry();
    virtual ~FilePlanEntry();

  public slots:
    void setTitle(const QString &title);
    QString title() const;

    void setRefNo(const QString &ref_no);
    QString refNo() const;

    void setComment(const QString &comment);
    QString comment() const;

  private:
    QString   m_title;          // Title.
    QString   m_ref_no;         // Reference number.
    QString   m_comment;
};

