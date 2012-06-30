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

#include <QDir>

#include "Database.h"
#include "Table.h"

const char *Database::m_identifier = "open-egovernment://database/0.1";

Database::Database(const QString &databaseName)
{
  open(databaseName, true);
}

Database::~Database()
{
  close();
}

bool Database::open(const QString &databaseName, bool createDB /*=false*/)
{
  if (databaseName.length() <= 0)
    return false;

  if (createDB && !exists(databaseName))
    create(databaseName);

  m_database_name = databaseName;



  return true;
}

void Database::close()
{
  if (m_database_name.length() < 0)              // Not open.
    return;

  

  m_database_name = "";
}

bool Database::create(const QString &databaseName)
{
  if (databaseName.length() <= 0)
    return false;

  

  open(databaseName);

  return true;
}

bool Database::exists(const QString &databaseName)
{
  if (databaseName.length() <= 0)
    return false;

  

  return false;
}

bool Database::remove(const QString &databaseName)
{
  close();

  

  return true;
}

Table *Database::table(const QString &tableName, bool create /*=false*/)
{
  if (create && !existsTable(tableName))
    return createTable(tableName);

  Table *t = new Table();

  

  return t;
}

Table *Database::createTable(const QString &tableName)
{
  if (tableName.length() <= 0)
    return 0;

  Table *t = new Table();

  

  return t;
}

bool Database::existsTable(const QString &tableName)
{
  if (tableName.length() <= 0)
    return false;


  return true;
}

bool Database::removeTable(const QString &tableName)
{
  

  return true;
}

QStringList Database::tables() const
{
  return QStringList();
}

void Database::setPath(const QString &path)
{
  if (path.length() <= 0)
    return;

  m_path = path;
}

QString Database::path() const
{
  return m_path;
}

