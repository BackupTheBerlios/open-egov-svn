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
#include <QtNetwork>

#include "HTTPStatusCode.h"
#include "ResponseData.h"

ResponseData::ResponseData(QObject *parent, const QString &protocol, const unsigned int statusCode)
 : QObject(parent)
{
  m_data.clear();

  HTTPStatusCode code(this, statusCode);
  addLine(protocol + " " + code.statusCode() + " " + code.statusText());  // HTTP/1.x 200 OK
  addLine(date());                                                        // Date: Wed, 08 Jul 2009 06:54:51 GMT
  addLine(server());                                                      // Server: Apache/2.2.11
}

void ResponseData::addLine(const QString &line)
{
  qDebug() << line;

  if (line.length() > 0) {
    m_data.append(line);
  }
}

QString ResponseData::data() const
{
  QString s = m_data.join("\r\n");

  s += "\r\n";

/*
Last-Modified: Fri, 18 Jul 2008 09:24:36 GMT
Content-Length: 259
Content-Type: image/gif
X-Cache: HIT from tg-fw.lfd.lsa-net.de
X-Cache-Lookup: HIT from tg-fw.lfd.lsa-net.de:3128
Proxy-Connection: keep-alive

Content-Type: image/gif
X-Cache: MISS from tg-fw.lfd.lsa-net.de
X-Cache-Lookup: MISS from tg-fw.lfd.lsa-net.de:3128
Proxy-Connection: close

    QString      m_protocol;
    unsigned int m_status_code
    QString      m_host_name;
    QString      m_content_type;
    unsigned int m_content_length;
    QString      m_proxy_connection;
*/

  return s;
}

void ResponseData::setContentType(const QString &ct)
{
  QString line = "Content-Type: " + ct;

  addLine(line);
}

void ResponseData::setContentLength(const unsigned int l)
{
  QString line = "Content-Length: " + QString::number(l);

  addLine(line);
}

void ResponseData::setLastModified(const QDateTime &dt)
{
  QString line = "Last-Modified: " + ResponseData::timeStamp(dt);

  addLine(line);
}

QString ResponseData::date() const
{
  return ResponseData::timeStamp(QDateTime::currentDateTime());
}

QString ResponseData::timeStamp(const QDateTime &dt)
{
  QString s = "Date: ";

  QDate d = dt.date();
  QString shortDayName = d.shortDayName(d.day());
  QString shortMonthName = d.shortMonthName(d.month());
  QString shortParts = dt.toString("yyyy hh:mm:ss");

  // TODO: currently only a constant time zone.
  s += QString("%1, %2 %3 %4 +0200").arg(shortDayName, QString::number(d.day()), shortMonthName, shortParts);

  //qDebug() << "ResponseData::timeStamp(): " << s;

  return s;
}

QString ResponseData::server() const
{
  return "Server: Open E-Government Application Server/0.0.1";
}

