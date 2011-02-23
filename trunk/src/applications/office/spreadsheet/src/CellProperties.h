// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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
#include <QColor>
#include <QFont>

class CellProperties : public QObject
{
  Q_OBJECT

  public:
    CellProperties();

  public:
    QString   m_name;
    int       m_span_row;
    int       m_span_column;
    QColor    m_fg_color;
    QColor    m_bg_color;
    //int       m_text_alignment;
    //QString   m_tool_tip;
    //QString   m_status_tip;
    //QFont     m_font;
};

