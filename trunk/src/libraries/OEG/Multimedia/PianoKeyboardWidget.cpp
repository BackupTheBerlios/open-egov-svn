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

#include <OEG/Multimedia/PianoKeyboardWidget.h>

#include <QString>
#include <QPainter>
#include <QPainterPath>
#include <QRect>

using namespace OEG::Multimedia;
using namespace Qt;

PianoKeyboardWidget::PianoKeyboardWidget(QWidget *parent /*=0*/)
 : QWidget(parent)
{
  m_white_key_width  = 23;
  m_white_key_height = 15;
  m_black_key_width  = 80;
  m_black_key_height = 50;
  m_active_key_color = Qt::yellow;
}

PianoKeyboardWidget::~PianoKeyboardWidget()
{
}

void PianoKeyboardWidget::setWhiteKeyWidth(const unsigned int value)
{
  m_white_key_width = value;
}

void PianoKeyboardWidget::setWhiteKeyHeight(const unsigned int value)
{
  m_white_key_height = value;
}

void PianoKeyboardWidget::setBlackKeyWidth(const unsigned int value)
{
  m_black_key_width = value;
}

void PianoKeyboardWidget::setBlackKeyHeight(const unsigned int value)
{
  m_black_key_height = value;
}

void PianoKeyboardWidget::setActiveKeyColor(const QColor color)
{
  m_active_key_color = color;
}

QColor PianoKeyboardWidget::activeKeyColor() const
{
  return m_active_key_color;
}

void PianoKeyboardWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setPen(Qt::black);


}

void PianoKeyboardWidget::mousePressEvent(QMouseEvent *event)
{
  Q_UNUSED(event)

}

void PianoKeyboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
  Q_UNUSED(event)

}

void PianoKeyboardWidget::mouseMoveEvent(QMouseEvent *event)
{
  Q_UNUSED(event)

}

