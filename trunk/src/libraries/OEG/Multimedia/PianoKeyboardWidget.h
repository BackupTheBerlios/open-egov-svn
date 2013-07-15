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

#include <QColor>
#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

#include <QDebug>

namespace OEG { namespace Multimedia {

class PianoKeyboardWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( unsigned int m_white_key_width  READ whiteKeyWidth  WRITE setWhiteKeyWidth  SCRIPTABLE true )
  Q_PROPERTY( unsigned int m_white_key_height READ whiteKeyHeight WRITE setWhiteKeyHeight SCRIPTABLE true )
  Q_PROPERTY( unsigned int m_black_key_width  READ blackKeyWidth  WRITE setBlackKeyWidth  SCRIPTABLE true )
  Q_PROPERTY( unsigned int m_black_key_height READ blackKeyHeight WRITE setBlackKeyHeight SCRIPTABLE true )
  Q_PROPERTY( QColor m_active_key_color       READ activeKeyColor WRITE setActiveKeyColor SCRIPTABLE true )

  public:
    enum PaperFormat {
      A1, A2, A3, A4, A5, A6
    };

  public:
    PianoKeyboardWidget(QWidget *parent = 0);
    virtual ~PianoKeyboardWidget();

    void setWhiteKeyWidth(const unsigned int value);
    void setWhiteKeyHeight(const unsigned int value);
    void setBlackKeyWidth(const unsigned int value);
    void setBlackKeyHeight(const unsigned int value);
    inline unsigned int whiteKeyWidth()  const { return m_white_key_width;  };
    inline unsigned int whiteKeyHeight() const { return m_white_key_height; };
    inline unsigned int blackKeyWidth()  const { return m_black_key_width;  };
    inline unsigned int blackKeyHeight() const { return m_black_key_height; };

    void setActiveKeyColor(const QColor color);
    QColor activeKeyColor() const;

  protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

  protected:
    unsigned int  m_white_key_width;
    unsigned int  m_white_key_height;
    unsigned int  m_black_key_width;
    unsigned int  m_black_key_height;
    QColor        m_active_key_color;
};

}}

