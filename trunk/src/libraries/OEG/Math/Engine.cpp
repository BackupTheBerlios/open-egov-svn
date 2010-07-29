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

#include <OEG/Math/Engine.h>

using namespace OEG::Math;
using namespace Qt;

Engine::Engine(QObject *parent /*=0*/)
 : QObject(parent)
{
}

Engine::~Engine()
{
}

// Resets the environment. Clears all variables and stacked values.

void Engine::clearEnvironment()
{
}

// Returns the result as QString.

QString Engine::compute(const QString &eq)
{
  m_error_message = "";

  

  return 0;
}

// Returns 0 if no errors found. Else the position of the first error in the string.
// Stores an error message.

unsigned int Engine::parseEquation(const QString &eq)
{
  m_error_message = "";

  

  return 0;
}

QString Engine::errorMessage() const
{
  return m_error_message;
}

