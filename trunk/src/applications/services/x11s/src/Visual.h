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

class Connection;

// Only one X visual is supported: 32-bit TrueColor.

class Visual : public QObject
{
  Q_OBJECT

  public:
    enum BackingStore {
      BS_NEVER        = 0,
      BS_WHEN_MAPPED  = 1,
      BS_STORE_ALWAYS = 2
    };

    enum VisualClass {
      VC_STATIC_GRAY  = 0,
      VC_GRAY_SCALE   = 1,
      VC_STATIC_COLOR = 2,
      VC_PSEUDO_COLOR = 3,
      VC_TRUE_COLOR   = 4,
      VC_DIRECT_COLOR = 5
    };

  public:
    Visual(int id, QObject *parent=0);
    virtual ~Visual();

    int id() const;
    quint8 getBackingStoreInfo() const;
    bool getSaveUnder() const;
    int depth() const;

    static void write(Connection *connection, int id);

  private:
    int  m_id;
};

