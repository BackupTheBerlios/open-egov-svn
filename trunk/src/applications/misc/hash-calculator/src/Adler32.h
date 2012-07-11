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
#include <QByteArray>
#include <QFile>
//#include <QMetaType>

#include "HashAlgorithm.h"

// Adler-32
// http://en.wikipedia.org/wiki/Adler-32
// The Adler-32 algorithm is much faster than the CRC32 algorithm yet
// still provides an extremely low probability of undetected errors.

class Adler32 : public HashAlgorithm
{
  Q_OBJECT

  public:
    Adler32();
    ~Adler32();

    virtual void initialize();
    virtual void finalize();

    QString hash(const QByteArray &data);

    static QString calcHash(const QByteArray &data);

  protected:
    quint32  m_a;
    quint32  m_b;
};

//Q_DECLARE_METATYPE(Adler32)

