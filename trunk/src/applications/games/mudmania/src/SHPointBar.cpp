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

#include <OEG/Common.h>

#include <QApplication>
#include <QColor>
#include <QLabel>
#include <QLatin1String>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

#include "SHPointBar.h"

SHPointBar::SHPointBar(QWidget *parent /*=0*/)
 : SplitterHandleWidget(parent)
{
  m_current_value = 0;
  m_min_value     = 0;
  m_max_value     = 100;

  setAutoFillBackground(true);
}

void SHPointBar::setCurrentValue(int value)
{
  m_current_value = value;
}

int SHPointBar::currentValue()
{
  return m_current_value;
}

void SHPointBar::setRange(int min, int max)
{
  m_min_value = min;
  m_max_value = max;
}

int SHPointBar::minValue()
{
  return m_min_value;
}

int SHPointBar::maxValue()
{
  return m_max_value;
}

void SHPointBar::paintEvent(QPaintEvent *event)
{
  //QWidget::paintEvent();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QColor barColor(  0, 255,   0);

  painter.setPen(Qt::SolidLine); // Qt::NoPen
  painter.setBrush(barColor);

  painter.fillRect(1, 1, 200, 20, Qt::blue);

  //painter.setPen(Qt::blue);
  //painter.setFont(QFont("Arial", 30));
  //painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

