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
#include <QStringList>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class WebPage : public QObject
{
  Q_OBJECT

  public:
    WebPage(QObject *parent = 0);

    void setHttpHeaderLine(const QString &s);
    QString httpHeader() const;

    void build();
    QString source() const;
    unsigned int length() const;

    void setTitle(const QString &title);
    void setContents(const QString &contents);

  private:
    void clear();

  private:
    QStringList m_http_header;
    QStringList m_head;
    QString     m_contents;
    QString     m_title;
    QString     m_dtd;
    QString     m_source;
    bool        m_need_build;
};

