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

#include <OEG/Common.h>

#include <QHash>
#include <QObject>
#include <QList>
#include <QString>

namespace OEG { namespace OpenStreetMap {

class Changeset : public QObject
{
  Q_OBJECT

  private:
    Changeset() {}

  public:
    Changeset(QObject *parent, unsigned int id, const QString &user, unsigned int uid, const QString &created_at_time,
              const QString &closed_at_time, bool open,
              const double min_lon, const double min_lat, const double max_lon, const double max_lat);
    //bool visible, unsigned int version, unsigned int changeset, QString timestamp
    ~Changeset();

  protected:
    QHash<QString, QString>  m_tags;
    unsigned int             m_id;
    QString                  m_user;
    unsigned int             m_uid;
    QString                  m_created_at_time;
    QString                  m_closed_at_time;
    bool                     m_open;
    double                   m_min_lon;
    double                   m_min_lat;
    double                   m_max_lon;
    double                   m_max_lat;
//    bool                     m_visible;
//    unsigned int             m_version;
//    unsigned int             m_changeset;
//    QString                  m_timestamp;
};

}}

