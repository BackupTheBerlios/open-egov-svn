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

#include <QFile>
#include <QDebug>
#include <QByteArray>

//#include <OEG/Hash/SHA2.h>

#include "SHA2.h"

SHA2::SHA2()
 : HashAlgorithm()
{
}

SHA2::~SHA2()
{
}

// =======================================

SHA256::SHA256()
{
  m_sha_type            = SHA2::SHA256;
  m_hash_algorithm_name = "SHA-256";

  initialize();
}

SHA256::~SHA256()
{
}

void SHA256::initialize()
{
  HashAlgorithm::initialize();

}

void SHA256::finalize()
{
  HashAlgorithm::finalize();

}

// This method accepts an array of octets as the next portion
// of the message.

void SHA256::hash(const QByteArray &data)
{
  unsigned int length = data.length();

  if (length <= 0)
    return; // Okay.

  //update((unsigned char *)data.data(), length);
}


// =======================================

SHA224::SHA224()
{
  m_sha_type            = SHA2::SHA224;
  m_hash_algorithm_name = "SHA-224";

  initialize();
}

SHA224::~SHA224()
{
}

void SHA224::finalize()
{
  SHA256::finalize(); //?

}

// =======================================

SHA512::SHA512()
{
  m_sha_type            = SHA2::SHA512;
  m_hash_algorithm_name = "SHA-512";

  initialize();
}

SHA512::~SHA512()
{
}

void SHA512::initialize()
{
  HashAlgorithm::initialize();

}

void SHA512::finalize()
{
  HashAlgorithm::finalize();

}

// This method accepts an array of octets as the next portion
// of the message.

void SHA512::hash(const QByteArray &data)
{
  unsigned int length = data.length();

  if (length <= 0)
    return; // Okay.

  //update((unsigned char *)data.data(), length);
}


// =======================================

SHA384::SHA384()
{
  m_sha_type            = SHA2::SHA384;
  m_hash_algorithm_name = "SHA-384";

  initialize();
}

SHA384::~SHA384()
{
}

void SHA384::finalize()
{
  SHA512::finalize(); // ??

}

