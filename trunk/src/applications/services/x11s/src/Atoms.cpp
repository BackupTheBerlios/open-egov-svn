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

Atoms::Atoms(QObject *parent/*=0*/)
 : QObject(parent), m_max_atom_id(0)
{
  m_predefined_atom_names
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

  registerPredefinedAtoms();
}

Atoms::~Atoms()
{
  foreach(Atom *atom, m_atoms_by_id.values())
    delete atom;

  m_atoms_by_id.clear();
  m_atoms_by_name.clear();
}

void Atoms::registerPredefinedAtoms()
{
  for (int i=0; i<m_predefined_atom_names.count(); i++)
    registerAtom(i + 1, m_predefined_atom_names[i]);
}

int Atoms::numberOfPredefinedAtoms() const
{
  return m_predefined_atom_names.count();
}

void Atoms::registerAtom(int id, const QString &name)
{
  Atom *atom = new Atom(this, id, name);

  if (! atom)
    return;

  addAtom(atom);
}

void Atoms::addAtom(Atom *atom)
{
  if (! atom)
    return;

  m_atoms_by_id[atom->atomID()]     = atom;
  m_atoms_by_name[atom->atomName()] = atom;

  int i = atom->atomID();
  if (i > m_max_atom_id)
    m_max_atom_id = i;
}

Atom *Atoms::getAtom(int id) const
{
  if (! m_atoms_by_id.contains(id))
    return 0;

  return m_atoms_by_id[id];
}

Atom *Atoms::findAtom(const QString &name) const
{
  if (! m_atoms_by_name.contains(name))
    return 0;

  return m_atoms_by_name[name];
}

void Atoms::reset()
{
  if (m_atoms_by_id.count() != m_predefined_atom_names.count()) {
    foreach(Atom* atom, m_atoms_by_id.values())
      delete atom;

    m_atoms_by_id.clear();
    m_atoms_by_name.clear();

    registerPredefinedAtoms();
  }
}

