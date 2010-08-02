// $Id$
//
// Open-eGovernment
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

#include <QWidget>
#include <QList>
#include <QString>

class QAction;
class QMouseEvent;
class QPaintEvent;

namespace OEG { namespace GIS {

class MapWidget : public QWidget
{
  Q_OBJECT

  public:
    enum MapEngine {
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
      None                                       // Do nothing.
    };

  public:
    MapWidget(QWidget *parent = 0);
    ~MapWidget();

  protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  protected:
    MapEngine      m_engine;
    LeftMouseMode  m_lmb_mode;

    float   m_box_left;
    float   m_box_right;
    float   m_box_top;
    float   m_box_bottom;
};

}}

