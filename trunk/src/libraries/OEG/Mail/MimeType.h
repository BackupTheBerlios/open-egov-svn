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

#pragma once

#include <QObject>
#include <QString>
#include <QList>

#include <QDebug>

namespace OEG { namespace Mail {

class MimeType : public QObject
{
  Q_OBJECT

  public:
    MimeType(const QString &type = "", const QString &sub_type = "", QObject *parent = 0);

    QString type() const { return m_type; }
    QString subType() const { return m_sub_type; }

    QString text();

  protected:
    QString  m_type;
    QString  m_sub_type;
};

}}
