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

class MD5 : public HashAlgorithm, public HashAlgorithmStaticMethods<MD5>
{
  Q_OBJECT

  public:
    MD5();
    ~MD5();

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);

  protected:
    static void decode(quint32 *output, unsigned char *input, unsigned int len);
    static void encode(unsigned char *output, quint32 *input, unsigned int len);
    static void transform(quint32 state[4], unsigned char block[64]);
    void update(unsigned char *input, unsigned int inputLen);

  protected:
    quint32 m_state[4];                                    // State (ABCD).
    quint32 m_count[2];                                    // Number of bits, modulo 2^64 (lsb first).
    quint8  m_buffer[64];                                  // Input buffer.
    quint8  m_digest[16];                                  // unsigned char.

    static unsigned char m_padding[64];
};

