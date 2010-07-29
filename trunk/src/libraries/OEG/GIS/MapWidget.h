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

namespace OEG { namespace Qt {

class MapWidget : public QWidget
{
  Q_OBJECT

  enum Engine {
    Custom,
    GoogleMaps,
    OpenStreetMap
  };

  public:
    MapWidget(QWidget *parent = 0);
    ~MapWidget();

  protected:

  protected:
    Engine  m_engine;
    float   m_box_left;
    float   m_box_right;
    float   m_box_top;
    float   m_box_bottom;
};

}}

