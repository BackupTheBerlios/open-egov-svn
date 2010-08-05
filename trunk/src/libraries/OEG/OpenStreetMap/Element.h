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

class Element : public QObject
{
  Q_OBJECT

  private:
    Element() {}

  public:
    Element(QObject *parent, unsigned int id, const QString &user, unsigned int uid, bool visible,
            unsigned int version, unsigned int changeset, QString timestamp);
    virtual ~Element();

    inline unsigned int id() { return m_id; }

    virtual QString toXML() = 0;

  protected:
    QString tagsToXML();

  protected:
    unsigned int             m_id;
    QString                  m_user;
    unsigned int             m_uid;
    bool                     m_visible;
    unsigned int             m_version;
    unsigned int             m_changeset;
    QString                  m_timestamp;
    QHash<QString, QString>  m_tags;

    bool                     m_changed;
};

}}

