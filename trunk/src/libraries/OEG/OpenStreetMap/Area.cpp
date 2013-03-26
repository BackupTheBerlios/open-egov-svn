// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <OEG/OpenStreetMap/Area.h>

#include <QDebug>
#include <QList>
#include <QLatin1String>

using namespace OEG::OpenStreetMap;
using namespace Qt;

Area::Area(QObject *parent, unsigned int id, const QString &user, unsigned int uid, bool visible, unsigned int version,
         unsigned int changeset, QString timestamp)
 : Way(parent, id, user, uid, visible, version, changeset, timestamp)
{
}

Area::~Area()
{
}

