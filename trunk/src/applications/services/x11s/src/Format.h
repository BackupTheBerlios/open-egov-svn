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

#include <QObject>
#include <QDebug>

class Connection;

class Format : public QObject
{
  Q_OBJECT

  public:
    Format(quint8 depth, quint8 bits_per_pixel, quint8 scan_line_pad_bits);
    virtual ~Format();

    void write(Connection *connection);

  private:
    quint8  m_depth;                              // Depth of a pixel in bits.
    quint8  m_bits_per_pixel;                     // Number of bits per pixel.
    quint8  m_scan_line_pad_bits;                 // Number of bits to pad each scan line.
};

