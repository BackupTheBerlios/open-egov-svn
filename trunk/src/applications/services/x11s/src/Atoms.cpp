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
#include <QStringList>

#include "Atom.h"
#include "Atoms.h"

Atoms::Atoms(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_predefined_atoms
    << "PRIMARY"            << "SECONDARY"          << "ARC"                << "ATOM"
    << "BITMAP"             << "CARDINAL"           << "COLORMAP"           << "CURSOR"
    << "CUT_BUFFER0"        << "CUT_BUFFER1"        << "CUT_BUFFER2"        << "CUT_BUFFER3"
    << "CUT_BUFFER4"        << "CUT_BUFFER5"        << "CUT_BUFFER6"        << "CUT_BUFFER7"
    << "DRAWABLE"           << "FONT"               << "INTEGER"            << "PIXMAP"
    << "POINT"              << "RECTANGLE"          << "RESOURCE_MANAGER"   << "RGB_COLOR_MAP"
    << "RGB_BEST_MAP"       << "RGB_BLUE_MAP"       << "RGB_DEFAULT_MAP"    << "RGB_GRAY_MAP"
    << "RGB_GREEN_MAP"      << "RGB_RED_MAP"        << "STRING"             << "VISUALID"
    << "WINDOW"             << "WM_COMMAND"         << "WM_HINTS"           << "WM_CLIENT_MACHINE"
    << "WM_ICON_NAME"       << "WM_ICON_SIZE"       << "WM_NAME"            << "WM_NORMAL_HINTS"
    << "WM_SIZE_HINTS"      << "WM_ZOOM_HINTS"      << "MIN_SPACE"          << "NORM_SPACE"
    << "MAX_SPACE"          << "END_SPACE"          << "SUPERSCRIPT_X"      << "SUPERSCRIPT_Y"
    << "SUBSCRIPT_X"        << "SUBSCRIPT_Y"        << "UNDERLINE_POSITION" << "UNDERLINE_THICKNESS"
    << "STRIKEOUT_ASCENT"   << "STRIKEOUT_DESCENT"  << "ITALIC_ANGLE"       << "X_HEIGHT"
    << "QUAD_WIDTH"         << "WEIGHT"             << "POINT_SIZE"         << "RESOLUTION"
    << "COPYRIGHT"          << "NOTICE"             << "FONT_NAME"          << "FAMILY_NAME"
    << "FULL_NAME"          << "CAP_HEIGHT"         << "WM_CLASS"           << "WM_TRANSIENT_FOR";
}

Atoms::~Atoms()
{
  while (! m_atoms.isEmpty()) {
    Atom *a = m_atoms.takeFirst();
    if (a) {
      delete a;
    }
  }
}

void Atoms::registerPredefinedAtoms()
{
  for (int i=0; i<m_predefined_atoms.count(); i++)
    addAtom(new Atom(i + 1, m_predefined_atoms[i]));
}

int Atoms::numberOfPredefinedAtoms() const
{
  return m_predefined_atoms.count();
}

void Atoms::addAtom(Atom *atom)
{
  if (atom)
    m_atoms.append(atom);
}

