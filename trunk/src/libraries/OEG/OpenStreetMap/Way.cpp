// $Id: MapWidget.cpp 246 2010-08-04 18:58:33Z gerrit-albrecht $
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

#include <QDebug>
#include <QList>
#include <QLatin1String>

#include <OEG/OpenStreetMap/Way.h>
#include <OEG/OpenStreetMap/Node.h>
#include <OEG/OpenStreetMap/Client.h>

using namespace OEG::OpenStreetMap;
using namespace Qt;

Way::Way(QObject *parent, unsigned int id, const QString &user, unsigned int uid, bool visible, unsigned int version,
         unsigned int changeset, QString timestamp)
 : Element(parent, id, user, uid, visible, version, changeset, timestamp)
{
}

Way::~Way()
{
}

QString Way::nodesToXML()
{
  QString s;

  for (int i=0; i<m_nodes.size(); i++) {
    Node *n = m_nodes.at(i);
    if (! n)
      continue;
    s += "<nd ref='" + QString::number(n->id()) + "' />";
  }

  return s;
}

QString Way::toXML()
{
  QString s;

  s += "<osm version='0.6' generator='" + Client::generator() + "'>";
  s += "<way ";
  s +=   "changeset='" + QString::number(m_changeset) + "' ";
  s +=   "id='" + QString::number(m_id) + "' ";
  s +=   "user='" + m_user + "' ";
  s +=   "uid='" + QString::number(m_uid) + "' ";
  s +=   "visible='" + (m_visible) ? "true" : "false" + QLatin1String("' ");
  s +=   "version='" + QString::number(m_version) + "' ";
  s +=   "timestamp='" + m_timestamp + "'";
  s += ">";
  s += tagsToXML();
  s += nodesToXML();
  s += "</way>";
  s += "</osm>";

  return s;
}

#if 0
http://www.openstreetmap.org/api/0.6/way/601
way id="601" ="true" ="2009-04-07T09:07:55Z" ="3"

<tag k="created_by" v="osmeditor2"/>
<tag k="designation" v="public_footpath"/>
<tag k="foot" v="yes"/>
<tag k="highway" v="footway"/>

<tag k="highway" v="secondary"/>
<tag k="lanes" v="2"/>
<tag k="maxspeed" v="50"/>
<tag k="name" v="Gelsenkirchener Straße"/>
<tag k="oneway" v="yes"/>
<tag k="ref" v="K 21"/>
#endif

