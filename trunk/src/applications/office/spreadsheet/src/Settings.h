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
#include <OEG/Qt/Application.h>
#include <OEG/Qt/Settings.h>

#include <QObject>
#include <QColor>
#include <QString>

class Settings : public OEG::Qt::Settings
{
  Q_OBJECT

  public:
    Settings();

  protected:
    bool load();
    bool save();

  private slots:

  public: // TODO: protect.
    bool     m_hide_header_hor;
    bool     m_hide_header_ver;
    bool     m_r1c1_mode;
    bool     m_show_grid;
    QColor   m_grid_color;
    QString  m_charset;
    int      m_charset_start;
    int      m_charset_size;
};

