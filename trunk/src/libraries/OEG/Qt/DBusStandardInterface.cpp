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

#include <OEG/Common.h>
#include <OEG/Qt/Application.h>
#include <OEG/Qt/DBusStandardInterface.h>

#include <QMessageBox>
#include <QStringList>
//#include <QDBusConnection>
#include <QSettings>
#include <QDebug>

using namespace OEG::Qt;
using namespace Qt;

DBusStandardInterface::DBusStandardInterface(QObject *parent /*=0*/)
 : QObject(parent)
{
#if 0
  QDBusConnection::sessionBus().registerObject(QLatin1String("/"), this,
                                               QDBusConnection::ExportScriptableSlots);
#endif
}

void DBusStandardInterface::stopWithSessionSave() const
{
}

void DBusStandardInterface::startWithSessionLoad() const
{
}

void DBusStandardInterface::exit()
{
}

QString DBusStandardInterface::baseName() const
{
  return QString("testname");
}

void DBusStandardInterface::setBaseName(const QString &name)
{
}

