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

#include <OEG/Common.h>

#include <QObject>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QDebug>

namespace OEG { namespace Qt {

class ConnectorMessage : public QObject
{
  public:
    ConnectorMessage(QObject *parent = 0);
    ~ConnectorMessage();

    bool validChecksum();
    QString toString();

  protected:
    void updateChecksum();
    void updateDateTime();

  public:
    QString   m_from;
    QString   m_to;
    QString   m_text;
    QString   m_checksum;
    QDateTime m_date_time;
};

}}

