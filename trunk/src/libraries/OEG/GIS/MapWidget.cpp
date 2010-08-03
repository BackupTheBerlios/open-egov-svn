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

#include <OEG/GIS/MapWidget.h>

#include <QKeySequence>
#include <QList>
#include <QLatin1String>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>

using namespace OEG::GIS;
using namespace Qt;

MapWidget::MapWidget(QWidget *parent /*=0*/)
 : QWidget(parent)
{
  m_engine      = OpenStreetMap;
  m_lmb_mode    = None;
  m_render_mode = Tiles;

  m_area_left   = 0.0;
  m_area_right  = 0.0;
  m_area_top    = 0.0;
  m_area_bottom = 0.0;

}

MapWidget::~MapWidget()
{
}

void MapWidget::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
  QWidget::mousePressEvent(event);

}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
  QWidget::mouseReleaseEvent(event);

}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
  QWidget::mouseMoveEvent(event);

}

void MapWidget::setZoom(int zoom)
{
  m_zoom = zoom;
}

void MapWidget::setArea(double left, double top, double right, double bottom)
{
  m_area_left   = left;
  m_area_top    = top;
  m_area_right  = right;
  m_area_bottom = bottom;

}
