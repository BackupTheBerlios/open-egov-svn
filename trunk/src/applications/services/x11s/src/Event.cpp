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
#include "Event.h"

Event::Event(QObject *parent/*=0*/)
 : QObject(parent)
{
}

Event::~Event()
{
}

// Sends an event header to the client.

void Event::writeHeader(Connection *connection, int code, int argument/*=0*/)
{
  if (! connection)
    return;

  connection->writeByte(code);
  connection->writeByte(argument);
  connection->writeShort(connection->sequenceNumber() & 0xffff);
}

