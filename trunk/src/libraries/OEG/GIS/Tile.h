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

#include <QList>
#include <QPixmap>
#include <QString>
#include <QUrl>

namespace OEG { namespace GIS {

class Tile : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QPixmap m_map READ map WRITE setMap)

  public:
    Tile(QObject *parent = 0);
    ~Tile();

    void setImage(const QString &fileName, double left, double top, double right, double bottom);

    inline double left()   const { return m_area_left; }
    inline double top()    const { return m_area_top; }
    inline double right()  const { return m_area_right; }
    inline double bottom() const { return m_area_bottom; }

  public slots:
    void load();

  protected:
    inline QPixmap map() const
    {
      return m_map;
    }

    inline void setMap(const QPixmap &map)
    {
      m_map = map;
      emit mapChanged();
    }

  signals:
    void mapChanged();

  protected:
    QPixmap        m_map;
    QString        m_file_name;
    QUrl           m_url;
    bool           m_loaded;
    double         m_area_left;        // Longitude of the left (westernmost) side of the bounding box.
    double         m_area_top;         // Latitude of the top (northernmost) side of the bounding box.
    double         m_area_right;       // Longitude of the right (easternmost) side of the bounding box.
    double         m_area_bottom;      // Latitude of the bottom (southernmost) side of the bounding box.
};

}}

