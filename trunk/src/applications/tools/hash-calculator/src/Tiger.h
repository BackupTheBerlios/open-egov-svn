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

// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991.
// All rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
//
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
//
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
//
// These notices must be retained in any copies of any part of this
// documentation and/or software.

#pragma once

#include <OEG/Common.h>

#include <QObject>
#include <QByteArray>
#include <QFile>

#include "HashAlgorithm.h"

class TigerBase : public HashAlgorithm
{
  Q_OBJECT

  public:
    TigerBase();

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);

  protected:
    void update(unsigned char *input, unsigned int inputLen);

    void compressBlock(const QByteArray &block);
    void round(quint64 *a, quint64 *b, quint64 *c, quint64 x, quint64 mul);
    void pass(quint64 *a, quint64 *b, quint64 *c, quint64 mul);
    void keySchedule();

  protected:
    quint64        m_a, m_b, m_c;                          // State.

    quint64        m_length;
    quint64        m_block[8];                             // Work area for the algorithm.
    QByteArray     m_buffer;                               // Input buffer.

    static quint64 m_table_1[256];
    static quint64 m_table_2[256];
    static quint64 m_table_3[256];
    static quint64 m_table_4[256];
};

class Tiger : public TigerBase, public HashAlgorithmStaticMethods<Tiger>
{
  Q_OBJECT

  public:
    Tiger();

    virtual void finalize();
};

class Tiger2 : public TigerBase, public HashAlgorithmStaticMethods<Tiger2>
{
  Q_OBJECT

  public:
    Tiger2();

    virtual void finalize();
};

