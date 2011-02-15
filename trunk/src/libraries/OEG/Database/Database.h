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

#include <QObject>
#include <QList>
#include <QString>

namespace OEG { namespace Database {

class Database : public QObject
{
  Q_OBJECT

  public:
    enum DatabaseSystem { XML, SQLITE, MYSQL };
    enum DatabaseType   { LOCAL, REMOTE, CLOUD, PEERTOPEER };
    enum DatabaseAccess { PRIVATE, WORKGROUP, PUBLIC };
    enum DatabaseRights { READ, WRITE, ADD, DELETE };

  public:
    Database(QObject *parent);
    ~Database();

    void addDatabase(DatabaseSystem system, DatabaseType type,
                     DatabaseAccess access, DatabaseRights rights);
  protected:

};

}}

