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

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class Session : public QObject
{
  Q_OBJECT

  public:
    Session(QObject *parent = 0);

    void refresh();

  private slots:


  private:
    QString   m_session_id;

    QString   m_ip_number;
    QString   m_browser_id;
    bool      m_old_browser;
    bool      m_sent_no_support;
    bool      m_javascript;
    QDateTime m_time_started;
    QDateTime m_time_refresh;
};

