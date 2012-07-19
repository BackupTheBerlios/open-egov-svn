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

class SHA2 : public HashAlgorithm
{
  Q_OBJECT

  public:
    enum SecureHashAlgorithm { SHA256, SHA224, SHA512, SHA384 };

  public:
    SHA2();
    ~SHA2();

    virtual int outputSize() = 0;                          // In bytes.
    virtual int internalStateSize() = 0;                   // In bytes.
    virtual int blockSize() = 0;                           // In bytes.
    virtual int wordSize() = 0;                            // In bytes.
    virtual int rounds() = 0;

  protected:
    SecureHashAlgorithm  m_sha_type;
};

class SHA256 : public SHA2, public HashAlgorithmStaticMethods<SHA256>
{
  Q_OBJECT

  public:
    SHA256();
    ~SHA256();

    virtual inline int outputSize() { return 32; }         // 256 bits.
    virtual inline int internalStateSize() { return 32; }  // 256 bits.
    virtual inline int blockSize() { return 64; }          // 512 bits.
    virtual inline int wordSize() { return 4; }            // 32 bits.
    virtual inline int rounds() { return 64; }             

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);
};

class SHA224 : public SHA256, public HashAlgorithmStaticMethods<SHA224>
{
  Q_OBJECT

  public:
    SHA224();
    ~SHA224();

    virtual inline int outputSize() { return 28; }         // 224 bits.

    virtual void finalize();
};

class SHA512 : public SHA2, public HashAlgorithmStaticMethods<SHA512>
{
  Q_OBJECT

  public:
    SHA512();
    ~SHA512();

    virtual inline int outputSize() { return 64; }
    virtual inline int internalStateSize() { return 64; }
    virtual inline int blockSize() { return 128; }
    virtual inline int wordSize() { return 8; }
    virtual inline int rounds() { return 80; }

    virtual void initialize();
    virtual void finalize();

    void hash(const QByteArray &data);
};

class SHA384 : public SHA512, public HashAlgorithmStaticMethods<SHA384>
{
  Q_OBJECT

  public:
    SHA384();
    ~SHA384();

    virtual inline int outputSize() { return 48; }         // 384 bits.

    virtual void finalize();
};

