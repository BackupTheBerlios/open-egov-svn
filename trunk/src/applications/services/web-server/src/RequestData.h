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

#pragma once

#include <OEG/Common.h>

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QStringList>

class RequestData : public QObject
{
  Q_OBJECT

  public:
    RequestData(QObject *parent = 0);

    void addLine(const QString &line);
    void clear();

    QString hostName() const;
    QString requestMethod() const;
    QString url() const;
    QString protocol() const;
    QString userAgent() const;
    unsigned int keepAlive() const;
    QString connection() const;
    QString proxyConnection() const;
    QString referer() const;

  protected:
    void parseLine(const QString &line);

  private:
    QStringList  m_data;

    QString      m_host_name;
    QString      m_request_method;
    QString      m_url;
    QString      m_protocol;
    QString      m_user_agent;
    unsigned int m_keep_alive;
    QString      m_connection;
    QString      m_proxy_connection;
    QString      m_referer;
    QString      m_accept;
    QString      m_accept_language;
    QString      m_accept_encoding;
    QString      m_accept_charset;
};

