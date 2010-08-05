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

#include <OEG/OpenStreetMap/Element.h>

#include <QDebug>
#include <QHash>
#include <QHashIterator>
#include <QList>
#include <QLatin1String>

using namespace OEG::OpenStreetMap;
using namespace Qt;

Element::Element(QObject *parent, unsigned int id, const QString &user, unsigned int uid,
                 bool visible, unsigned int version, unsigned int changeset, QString timestamp)
 : QObject(parent), m_id(id), m_user(user), m_uid(uid), m_visible(visible),
   m_version(version), m_changeset(changeset), m_timestamp(timestamp)
{
  m_changed = false;

  if (m_timestamp.length() <= 0) {
    //m_timestamp = "2010-08-05T08:00:00Z";  // NEEDED? BUILD OWN?
  }
}

Element::~Element()
{
}

QString Element::tagsToXML()
{
  QString s;
  QHashIterator<QString, QString> i(m_tags);

  while (i.hasNext()) {
    i.next();
    s += "<tag k='" + i.key() + "' v='" + i.value() + "' />";
  }

  return s;
}

