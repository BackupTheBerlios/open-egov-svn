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
#include "Visual.h"

Visual::Visual(int id, QObject *parent/*=0*/)
 : QObject(parent)
{
  m_id = id;
}

Visual::~Visual()
{
}

int Visual::id() const
{
  return m_id;
}

// Return whether the visual supports a backing store.

quint8 Visual::getBackingStoreInfo() const
{
  return BS_STORE_ALWAYS;
}

// Return whether the visual supports save-under.

bool Visual::getSaveUnder() const
{
  return false;
}

// Returns  the depth of the visual in bits. This is always 32, there is no reason to support less.

int Visual::depth() const
{
  return 32;
}

// Write details of the visual.

void Visual::write(Connection *connection, int id)
{
  if (! connection) {
    qDebug() << "Visual::write(): connection was zero.";
    return;
  }

  connection->writeInt(id);                                // Visual ID.
  connection->writeByte(VC_TRUE_COLOR);                    // Class.
  connection->writeByte(8);                                // Bits per RGB value.
  connection->writeShort(1 << 8);                          // Colormap entries.
  connection->writeInt(0x00ff0000);                        // Red mask.
  connection->writeInt(0x0000ff00);                        // Green mask.
  connection->writeInt(0x000000ff);                        // Blue mask.
  connection->writePaddingBytes(4);                        // Unused.

  connection->flush();
}

