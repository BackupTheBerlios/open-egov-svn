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

#include "HashAlgorithm.h"

class CRC32 : public HashAlgorithm, public HashAlgorithmStaticMethods<CRC32>
{
  Q_OBJECT

  public:
    CRC32();
    ~CRC32();

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);

  protected:
    //inline static CRC32 *createObject() { return new CRC32(); }

  protected:
    static const quint32 m_crc32_tab[];
    quint32              m_crc32;
};

