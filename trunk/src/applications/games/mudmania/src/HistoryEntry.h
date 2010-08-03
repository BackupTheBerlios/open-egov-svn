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

#pragma once

#include <OEG/Common.h>

#include <QColor>
#include <QDateTime>
#include <QString>
#include <QTextEdit>

class HistoryEntry : public QObject
{
  Q_OBJECT

  public:
    HistoryEntry(const QString &text);

    void setCurrentTime();
    QDateTime time();

  public:
    QString    m_text;
    QString    m_player_and_world;
    QColor     m_bg_color;
    QColor     m_fg_color;

  protected:
    QDateTime  m_time;
};

