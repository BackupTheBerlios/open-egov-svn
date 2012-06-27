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

#include <OEG/GIS/Tile.h>

#include <QDebug>
#include <QList>
#include <QLatin1String>
#include <QPoint>

using namespace OEG::GIS;
using namespace Qt;

Tile::Tile(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_loaded      = false;
  m_file_name   = "";
  m_area_left   = 0.0;
  m_area_right  = 0.0;
  m_area_top    = 0.0;
  m_area_bottom = 0.0;
}

Tile::~Tile()
{
}

void Tile::setImage(const QString &fileName, double left, double top, double right, double bottom)
{
  m_file_name   = fileName;
  m_loaded      = false;
  m_area_left   = left;
  m_area_right  = right;
  m_area_top    = top;
  m_area_bottom = bottom;
}

void Tile::load()
{
  m_map.load(m_file_name);
  if (m_map.isNull()) {
    qDebug() << "Tile::load() failed:" << m_file_name;
    return;
  }
}

