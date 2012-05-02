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

#include <OEG/Common.h>

#include <QObject>

#include "Connection.h"
#include "Format.h"

Format::Format(quint8 depth, quint8 bits_per_pixel, quint8 scan_line_pad_bits)
 : QObject(0)
{
  m_depth              = depth;                                      // Depth in bits.
  m_bits_per_pixel     = bits_per_pixel;                             // Bits per pixel.
  m_scan_line_pad_bits = scan_line_pad_bits;                         // Bits to pad each scan line.
}

Format::~Format()
{
}

void Format::write(Connection *connection)
{
  if (! connection)
    return;

  if (! connection->isValid())
    return;

  connection->writeByte(m_depth);                                   // Depth in bits.
  connection->writeByte(m_bits_per_pixel);                          // Bits per pixel.
  connection->writeByte(m_scan_line_pad_bits);                      // Bits to pad each scan line.
  connection->writePaddingBytes(5);                                 // Unused.
}

