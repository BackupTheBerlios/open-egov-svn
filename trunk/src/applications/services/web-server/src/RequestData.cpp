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

#include <QDebug>

#include "RequestData.h"

RequestData::RequestData(QObject *parent)
 : QObject(parent)
{
  clear();
}

void RequestData::addLine(const QString &line)
{
  qDebug() << "RequestData::addLine(): " << line;

  if (line.length() > 0) {
    m_data.append(line);

    parseLine(line);
  }
}

void RequestData::parseLine(const QString &line)
{
  if (line.startsWith("Host: ", Qt::CaseInsensitive)) {
    m_host_name = line.right(line.length() - 6);
    qDebug() << "  HOST: " << m_host_name;
  }
  else if (line.startsWith("User-Agent: ", Qt::CaseInsensitive)) {
    m_user_agent = line.right(line.length() - 12);
    qDebug() << "  UA: " << m_user_agent;
  }
  // http://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol
  else if (line.startsWith("GET ")) {
    m_request_method = "GET";
    QString s = line.right(line.length() - 4);
    int i = s.lastIndexOf(" ", -2);
    if (i != -1) {
      m_protocol = s.right(s.length() - (i+1));
      m_url = s.left(i);
    }
    qDebug() << "  Request Method: " << m_request_method;
    qDebug() << "  Protocol: " << m_protocol;
    qDebug() << "  URL: " << m_url;
  }
  else if (line.startsWith("POST ")) {
    m_request_method = line.right(line.length() - 5);
    qDebug() << "  Request Method: " << m_request_method;
  }
  else if (line.startsWith("Keep-Alive: ")) {
    m_keep_alive = line.right(line.length() - 12).toUInt();
    qDebug() << "  Keep-Alive: " << m_keep_alive;
  }
  else if (line.startsWith("Proxy-Connection: ")) {
    m_proxy_connection = line.right(line.length() - 18);
    qDebug() << "  Proxy-Connection: " << m_proxy_connection;
  }
  else if (line.startsWith("Connection: ")) {
    m_connection = line.right(line.length() - 12).toLower();
    qDebug() << "  Connection: " << m_connection;
  }
  else if (line.startsWith("Referer: ")) {
    m_referer = line.right(line.length() - 9);
    qDebug() << "  Referer: " << m_referer;
  }

  //str.indexOf(QRegExp("m[aeiou]"), 0)
}

void RequestData::clear()
{
  m_keep_alive = -1;
  m_connection = "";

  m_data.clear();
}

QString RequestData::hostName() const
{
  return m_host_name;
}

QString RequestData::requestMethod() const
{
  return m_request_method;
}

QString RequestData::url() const
{
  return m_url;
}

QString RequestData::protocol() const
{
  return m_protocol;
}

QString RequestData::userAgent() const
{
  return m_user_agent;
}

unsigned int RequestData::keepAlive() const
{
  return m_keep_alive;
}

QString RequestData::proxyConnection() const
{
  return m_proxy_connection;
}

QString RequestData::connection() const
{
  return m_connection;
}

QString RequestData::referer() const
{
  return m_referer;
}

#if 0
GET /icons/ho/mittelstandswiki.gif HTTP/1.1
Host: www.heise.de
User-Agent: Mozilla/5.0 (X11; U; Linux i686; de; rv:1.8.1.19) Gecko/20081202 Iceweasel/2.0.0.19 (Debian-2.0.0.19-0etch1aaamp1)
Accept: image/png,*__/__*;q=0.5
Accept-Language: de-de,de;q=0.8,en-us;q=0.5,en;q=0.3
Accept-Encoding: gzip,deflate
Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
Keep-Alive: 300
Proxy-Connection: keep-alive
Referer: http://www.heise.de/
#endif

