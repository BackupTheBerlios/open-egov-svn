// $Id$

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

