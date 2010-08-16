// $Id$
//
// G.A.S.I. Libraries Pack: Qt Extension Library
// Copyright (C) 2005-2008 by Gerrit M. Albrecht
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

#ifndef GASI_QT_COLORBUTTON_H
#define GASI_QT_COLORBUTTON_H

#include <QPushButton>
#include <QColor>

class ColorButton : public QPushButton
{
  Q_OBJECT
  Q_PROPERTY( QColor color READ color WRITE setColor )

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

#endif

