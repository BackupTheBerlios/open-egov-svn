// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <QObject>

class QByteArray;
class QString;
class QFile;

class DirectoryEntry : public QObject
{
  Q_OBJECT

  public:
    DirectoryEntry(QObject *parent = 0);

  public:                              // TODO: public; change and fix this class, if everything works.
    int           m_id;
    QByteArray    m_name;
    long long int m_type;
    long long int m_left_child;
    long long int m_right_child;
    long long int m_root_node;
    long long int m_sid_of_first_sector;
    long long int m_stream_size;
};

