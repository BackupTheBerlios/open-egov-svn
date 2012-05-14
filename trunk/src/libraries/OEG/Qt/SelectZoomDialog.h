// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
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

#include <QDialog>

#include "ui_select-zoom.h"

class SelectZoomDialog : public QDialog, public Ui::SelectZoomDialog
{
  Q_OBJECT

  public:
    SelectZoomDialog(QWidget *parent = 0);

    inline int minZoomLevel() const     { return m_min_zoom_level;     }
    inline int maxZoomLevel() const     { return m_max_zoom_level;     }
    inline int currentZoomLevel() const { return m_current_zoom_level; }

  protected:

  private slots:

  private:
    int  m_min_zoom_level;
    int  m_max_zoom_level;
    int  m_current_zoom_level;
};

