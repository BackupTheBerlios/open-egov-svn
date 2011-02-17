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
#include <QWidget>

#include "SplitterHandleWidget.h"

class QPaintEvent;

class SHPointBar : public SplitterHandleWidget
{
  Q_OBJECT

  public:
    SHPointBar(QWidget *parent = 0);

    void setCurrentValue(int value);
    int currentValue();

    void setRange(int min, int max);
    int minValue();
    int maxValue();

  protected:
    virtual void paintEvent(QPaintEvent *event);

  protected:
    int     m_current_value;
    int     m_min_value;
    int     m_max_value;
    QColor  m_color;
};

