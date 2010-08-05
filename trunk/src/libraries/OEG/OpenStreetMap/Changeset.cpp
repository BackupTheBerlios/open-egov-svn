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

#include <OEG/OpenStreetMap/Changeset.h>

#include <QDebug>
#include <QList>
#include <QLatin1String>

using namespace OEG::OpenStreetMap;
using namespace Qt;

Changeset::Changeset(QObject *parent, unsigned int id, const QString &user, unsigned int uid,
                     const QString &created_at_time, const QString &closed_at_time, bool open,
                     const double min_lon, const double min_lat,
                     const double max_lon, const double max_lat)
 : QObject(parent), m_id(id), m_user(user), m_uid(uid), m_created_at_time(created_at_time),
   m_closed_at_time(closed_at_time), m_open(open), m_min_lon(min_lon), m_min_lat(min_lat),
   m_max_lon(max_lon), m_max_lat(max_lat)
{
}

Changeset::~Changeset()
{
}

#if 0
http://www.openstreetmap.org/browse/changeset/5072090

<osm version="0.6" generator="OpenStreetMap server">
<changeset id="5072090" user="vogelfreier" uid="74746" created_at="2010-06-25T09:15:05Z" closed_at="2010-06-25T09:15:16Z" open="false" min_lon="7.029938" min_lat="51.4728817" max_lon="7.0531306" max_lat="51.4890081">
<tag k="comment" v="maxspeed 30/50"/>
<tag k="created_by" v="JOSM/1.5 (2255 SVN de)"/>
</changeset>
</osm>
#endif

