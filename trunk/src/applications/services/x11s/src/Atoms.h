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
#include <QString>
#include <QStringList>
#include <QHash>

class Atom;

class Atoms : public QObject
{
  Q_OBJECT

  public:
    Atoms(QObject *parent=0);
    virtual ~Atoms();

    void registerPredefinedAtoms();
    int numberOfPredefinedAtoms() const;
    void addAtom(Atom *atom);
    void reset();
    Atom *getAtom(int id) const;
    Atom *findAtom(const QString &name) const;

    inline int nextFreeAtomId() { return ++m_max_atom_id; }
    inline bool atomExists(int id) const { return m_atoms_by_id.contains(id); }

  protected:
    void registerAtom(int id, const QString &name);

  private:
    QStringList             m_predefined_atom_names;
    QHash<QString, Atom *>  m_atoms_by_name;
    QHash<int,     Atom *>  m_atoms_by_id;
    int                     m_max_atom_id;
};

