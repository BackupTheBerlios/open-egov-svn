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
#include <QDateTime>

class ResponseData : public QObject
{
  Q_OBJECT

  public:
    ResponseData(QObject *parent = 0, const QString &protocol = "HTTP/1.x", const unsigned int statusCode = 200);

    QString data() const;
    void addLine(const QString &line);

    void setContentType(const QString &ct);
    void setContentLength(const unsigned int l);
    void setLastModified(const QDateTime &dt);

  protected:
    QString date() const;
    QString server() const;

  private:
    static QString timeStamp(const QDateTime &dt);

  private:
    QStringList  m_data;
};

