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
#include "Error.h"

Error::Error(QObject *parent/*=0*/)
 : QObject(parent)
{
}

Error::~Error()
{
}

// Tells the client about an X11 error.

void Error::writeError(Connection *connection, ErrorCode errorcode, Request::RequestOpcode opcode, int id/*=0*/)
{
  if (! connection) {
    qDebug() << "Error::writeError(): connection was zero.";
    return;
  }

  connection->writeByte(0);                                          // Indicates an error.
  connection->writeByte(errorcode);                                  // Error code.
  connection->writeShort(connection->sequenceNumber() & 0xffff);     // Sequence number.
  connection->writeInt(id);                                          // ID of invalid resource (optional).
  connection->writeShort(0);                                         // Minor opcode.
  connection->writeByte(opcode);                                     // Major opcode.
  connection->writePaddingBytes(21);                                 // Unused.

  connection->flush();
}

