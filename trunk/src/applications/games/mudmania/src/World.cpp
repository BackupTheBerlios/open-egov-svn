// $Id$
//
// Open eGovernment
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

#include <QString>

#include "World.h"

World::World()
{
  m_id   = 0;
  m_host = "";
  m_port = 0;

  setName(_("Unnamed World"));
  setDescription("");
}

void World::setName(const QString &name)
{
  m_name = name;
}

QString World::name() const
{
  return m_name;
}

void World::setHost(const QString &host)
{
  m_host = host;
}

QString World::host() const
{
  return m_host;
}

void World::setPort(const unsigned int port)
{
  m_port = port;
}

unsigned int World::port() const
{
  return m_port;
}

void World::setDescription(const QString &description)
{
  m_description = description;
}

QString World::description() const
{
  return m_description;
}

void World::setHomepage(const QString &homepage)
{
  m_homepage = homepage;
}

QString World::homepage() const
{
  return m_homepage;
}

