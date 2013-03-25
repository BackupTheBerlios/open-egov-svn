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

#include <QtCore>

#include "HTTPStatusCode.h"

HTTPStatusCode::HTTPStatusCode(QObject *parent, const unsigned int statusCode)
 : QObject(parent), m_status_code(statusCode)
{
  m_data[100] = QLatin1String("Continue");
  m_data[101] = QLatin1String("Switching Protocols");
  m_data[200] = QLatin1String("OK");
  m_data[201] = QLatin1String("Created");
  m_data[202] = QLatin1String("Accepted");
  m_data[203] = QLatin1String("Non-Authoritative Information");
  m_data[204] = QLatin1String("No Content");
  m_data[205] = QLatin1String("Reset Content");
  m_data[206] = QLatin1String("Partial Content");
  m_data[300] = QLatin1String("Multiple Choices");
  m_data[301] = QLatin1String("Moved Permanently");
  m_data[302] = QLatin1String("Found");
  m_data[303] = QLatin1String("See Other");
  m_data[304] = QLatin1String("Not Modified");
  m_data[305] = QLatin1String("Use Proxy");
  m_data[307] = QLatin1String("Temporary Redirect");
  m_data[400] = QLatin1String("Bad Request");
  m_data[401] = QLatin1String("Unauthorized");
  m_data[402] = QLatin1String("Payment Required");
  m_data[403] = QLatin1String("Forbidden");
  m_data[404] = QLatin1String("Not Found");
  m_data[405] = QLatin1String("Method Not Allowed");
  m_data[406] = QLatin1String("Not Acceptable");
  m_data[407] = QLatin1String("Proxy Authentication Required");
  m_data[408] = QLatin1String("Request Time-out");
  m_data[409] = QLatin1String("Conflict");
  m_data[410] = QLatin1String("Gone");
  m_data[411] = QLatin1String("Length Required");
  m_data[412] = QLatin1String("Precondition Failed");
  m_data[413] = QLatin1String("Request Entity Too Large");
  m_data[414] = QLatin1String("Request-URI Too Large");
  m_data[415] = QLatin1String("Unsupported Media Type");
  m_data[416] = QLatin1String("Requested range not satisfiable");
  m_data[417] = QLatin1String("Expectation Failed");
  m_data[500] = QLatin1String("Internal Server Error");
  m_data[501] = QLatin1String("Not Implemented");
  m_data[502] = QLatin1String("Bad Gateway");
  m_data[503] = QLatin1String("Service Unavailable");
  m_data[504] = QLatin1String("Gateway Time-out");
  m_data[505] = QLatin1String("HTTP Version not supported");
}

QString HTTPStatusCode::statusCode() const
{
  return QString::number(m_status_code);
}

QString HTTPStatusCode::statusText() const
{
  return m_data[m_status_code];
}

