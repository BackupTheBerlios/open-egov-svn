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

#include <QDateTime>
#include <QString>
#include <QSqlQuery>

#include "ConnectionHistory.h"

ConnectionHistory::ConnectionHistory()
{
}

void ConnectionHistory::saveLogin(unsigned int player_id)
{
  QString dt = QDateTime::currentDateTime().toString(Qt::ISODate);
  QString pid = QString::number(player_id);
  QString sql;

  sql = "INSERT INTO logs (datetime, log_type_id, player_id) "
        "SELECT '" + dt + "', log_types.id, " + pid + " FROM log_types WHERE name='login'";

  //dynamic_cast<Database *>((dynamic_cast<MudMania *>(qApp))->database())->executeQuery(sql);
}

void ConnectionHistory::saveLogout(unsigned int player_id)
{
  QString dt = QDateTime::currentDateTime().toString(Qt::ISODate);
  QString pid = QString::number(player_id);
  QString sql;

  sql = "INSERT INTO logs (datetime, log_type_id, player_id) "
        "SELECT '" + dt + "', log_types.id, " + pid + " FROM log_types WHERE name='logout'";

  QSqlQuery query(sql);

  query.setForwardOnly(true);
  query.exec();
}

void ConnectionHistory::saveIdle(unsigned int player_id)
{
  QString dt = QDateTime::currentDateTime().toString(Qt::ISODate);
  QString pid = QString::number(player_id);
  QString sql;

  sql = "INSERT INTO logs (datetime, log_type_id, player_id) "
        "SELECT '" + dt + "', log_types.id, " + pid + " FROM log_types WHERE name='idle'";

}

void ConnectionHistory::saveActive(unsigned int player_id)
{
  QString dt = QDateTime::currentDateTime().toString(Qt::ISODate);
  QString pid = QString::number(player_id);
  QString sql;

  sql = "INSERT INTO logs (datetime, log_type_id, player_id) "
        "SELECT '" + dt + "', log_types.id, " + pid + " FROM log_types WHERE name='active'";

}

