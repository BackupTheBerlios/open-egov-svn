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
#include <QString>
#include <QStringList>
#include <QWidget>

#include <QDebug>

namespace OEG { namespace Pages {

class Page : public QWidget
{
  Q_OBJECT
  Q_ENUMS( PaperFormat )
  Q_PROPERTY( PaperFormat m_paper_format READ paperFormat WRITE setPaperFormat SCRIPTABLE true )
  Q_PROPERTY( unsigned int m_resolution READ resolution WRITE setResolution SCRIPTABLE true )
  Q_PROPERTY( QColor m_bg_color READ bgColor WRITE setBgColor SCRIPTABLE true )
  Q_PROPERTY( QColor m_fg_color READ fgColor WRITE setFgColor SCRIPTABLE true )

  public:
    enum PaperFormat {
      A1, A2, A3, A4, A5, A6
    };

  public:
    Page(QWidget *parent = 0);
    virtual ~Page();

    void writeText(unsigned long int x, unsigned long int y, const QString &text);
    void drawLine(unsigned long int x1, unsigned long int y1,
                  unsigned long int x2, unsigned long int y2);

    void setPaperFormat(const PaperFormat paperFormat);
    PaperFormat paperFormat() const;

    void setResolution(const unsigned int resolution);
    unsigned int resolution() const;

    void setFgColor(const QColor color);
    QColor fgColor() const;

    void setBgColor(const QColor color);
    QColor bgColor() const;

  protected:
    PaperFormat   m_paper_format;
    unsigned int  m_resolution;
    QColor        m_fg_color;
    QColor        m_bg_color;
};

}}

