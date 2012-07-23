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

class SHA1 : public HashAlgorithm, public HashAlgorithmStaticMethods<SHA1>
{
  Q_OBJECT

  public:
    SHA1();
    ~SHA1();

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);

  protected:
    void padMessage();
    void processMessageBlock();

  protected:
    quint32  m_intermediate_hash[5];
    quint32  m_length_low;
    quint32  m_length_high;
    quint16  m_message_block_index;                        // Original datatype: int_least16_t.
    quint8   m_message_block[64];                          // or: quint32 block[16]?
    bool     m_computed;
    bool     m_corrupted;
    quint8   m_final_digest[20];
};

