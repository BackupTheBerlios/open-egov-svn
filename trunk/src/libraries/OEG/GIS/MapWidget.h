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

#include <QWidget>
#include <QList>
#include <QString>

class QAction;
class QMouseEvent;
class QPaintEvent;

class Tile;

namespace OEG { namespace GIS {

class MapWidget : public QWidget
{
  Q_OBJECT

  public:
    enum MapFeature {
      SingleImage      =  1,
      Moveable         =  2,
      ZoomWidgets      =  4,
      MoveWidgets      =  8,
      MapScale         = 16,
      Overview         = 32,
      LoadingIndicator = 64
    };
    Q_DECLARE_FLAGS(MapFeatures, MapFeature)
    //typedef QFlags<MapFeature> MapFeatures;

    enum MapEngine {
      Images,                                    // Use images with map data.
      OpenStreetMap,                             // Download from OpenStreetMap.
      Google,                                    // Download from Google Maps.
      Yahoo,                                     // Download from Yahoo.
      DOPViewer,                                 // Use the DOP (Digitale Ortho Photos) Viewer.
      LSAViewer,                                 // Use the Land-Sachsen-Anhalt-Viewer.
      Custom                                     // Other services may be inserted.
    };

    enum LeftMouseMode {
      Pan,                                       // Move map.
      Drag,                                      // Select area.
      Zoom,                                      // Zoom into map.
      DragAndZoom,                               // Select area and zoom into it.
      None                                       // Do nothing.
    };

    enum RenderMode {                            // Only relevant for OSM data.
      Tiles,                                     // Display downloaded pictures and tile them.
      XML                                        // Render own tiles using SVG/Other engine.
    };

  public:
    MapWidget(QWidget *parent = 0);
    ~MapWidget();

    void setZoom(int zoom);
    int zoom() const;

    void setArea(double left, double top, double right, double bottom);

    void setImage(const QString &fileName, double left, double top, double right, double bottom, const bool singleImage = true);

  protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  signals:
    void coordinatesAtMouse(double, double);

  protected:
    MapEngine      m_engine;
    LeftMouseMode  m_lmb_mode;
    RenderMode     m_render_mode;

    MapFeatures    m_features;
    bool           m_valid_area;
    int            m_zoom;             // A value between -10000..0..+10000.
    double         m_area_left;        // Longitude of the left (westernmost) side of the bounding box.
    double         m_area_top;         // Latitude of the top (northernmost) side of the bounding box.
    double         m_area_right;       // Longitude of the right (easternmost) side of the bounding box.
    double         m_area_bottom;      // Latitude of the bottom (southernmost) side of the bounding box.
    QList<Tile *>  m_tiles;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MapWidget::MapFeatures)

}}

