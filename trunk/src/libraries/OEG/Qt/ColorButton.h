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

#include <QPushButton>
#include <QColor>

class QPaintEvent;
class QWidget;

namespace OEG { namespace Qt {

class ColorButton : public QPushButton
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)

  public:
    ColorButton(QWidget *parent = 0);
    ColorButton(const QColor &color, QWidget *parent = 0);
    ~ColorButton();

    QColor color () const;
    void setColor(const QColor &color);

  signals:
    void changed(const QColor &newColor);

  protected:
    virtual void paintEvent(QPaintEvent *e);

  protected slots:
    void chooseColor();

  private:
    QColor m_color;
};

}}

