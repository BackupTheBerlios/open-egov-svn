// $Id$
//
// Open-eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#include <OEG/Crypt/AES.h>

AES::AES()
 : m_rounds(0)
{
}

void AES::setRijndaelParameters(const QByteArray &key, int keyLength /*=128*/, int blockLength /*=128*/)
{
  m_length_state = blockLength / 8;                        // 16, 20, 24, 28, 32 bytes; AES: fixed to 128 bit = 16 bytes.
  m_length_key   = keyLength   / 8;                        // 16, 20, 24, 28, 32 bytes.

  m_rounds = numberOfRounds(keyLength, blockLength);

  // Calculate table sizes for state block and key block. Always 4 rows.
  int nb = m_length_state / 4;                             // The reason why the block length is always a multiple of 4.
  int nk = m_length_key   / 4;                             // We process a column vector containing always 4 rows.

  m_state = new uint8_t[4 * nb];
  m_key   = new uint8_t[4 * nk];


}

void AES::setAESParameters(const QByteArray &key, int keyLength /*=256*/)
{
  int length = keyLength;

  if (length <= 128)
    length = 128;
  else if (length > 192)
    length = 256;
  else
    length = 192;

  setRijndaelParameters(key, length, 128);
}

int AES::numberOfRounds(int keyLength /*=128*/, int blockLength /*=128*/)
{
  if ((blockLength == 256) || (keyLength == 256))
    return 14;
  if ((blockLength == 224) || (keyLength == 224))
    return 13;
  if ((blockLength == 192) || (keyLength == 192))
    return 12;
  if ((blockLength == 160) || (keyLength == 160))
    return 11;
  if ((blockLength == 128) && (keyLength == 128))
    return 10;

  return 0;                                                // Error.
}

QByteArray AES::expandKey(const QByteArray &key)
{
  if (m_rounds <= 0)
    return QByteArray();

  int eks = 16 * (m_rounds + 1);                           // Expanded key size.
  int rconIteration = 1;

  QByteArray ek(key);                                      // Initialize with input key.

    

  return ek;
}

uint8_t AES::forwardSBoxValue(int i)
{
  return m_forward_s_box[i];
}

uint8_t AES::reverseSBoxValue(int i)
{
  return m_reverse_s_box[i];
}

uint8_t AES::rconValue(int i)
{
  return m_rcon[i];
}

