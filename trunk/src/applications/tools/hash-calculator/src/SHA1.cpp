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

//#include <OEG/Crypt/SHA1.h>

#include "SHA1.h"

// Define the SHA1 circular left shift macro.

#define SHA1CircularShift(bits,word) (((word) << (bits)) | ((word) >> (32-(bits))))

SHA1::SHA1()
 : HashAlgorithm()
{
  m_hash_algorithm_name = "SHA-1";

  initialize(); // HashAlgorithm() ruft zwar initialize() auf, aber nur das Eigene!
}

SHA1::~SHA1()
{
}

void SHA1::initialize()
{
  HashAlgorithm::initialize();

  m_intermediate_hash[0] = 0x67452301;                     // Message Digest.
  m_intermediate_hash[1] = 0xefcdab89;
  m_intermediate_hash[2] = 0x98badcfe;
  m_intermediate_hash[3] = 0x10325476;
  m_intermediate_hash[4] = 0xc3d2e1f0;
  m_length_low           = 0;                              // Message length in bits.
  m_length_high          = 0;                              // Message length in bits.
  m_message_block_index  = 0;                              // Index into message block array.
  m_computed             = false;                          // Is the digest computed?
  m_corrupted            = false;                          // Is the message digest corrupted?
}

// This function will return the 160-bit message digest into the
// m_final_digest array. The first octet of hash is stored in the
// 0th element, the last octet of hash in the 19th element.

void SHA1::finalize()
{
  HashAlgorithm::finalize();

  const int BLOCK_SIZE = 64;
  const int HASH_SIZE  = 20;

  m_result = "";

  if (m_corrupted) {
    qDebug() << "Digest corrupted.";
    return;
  }

  if (! m_computed) {
    padMessage();

    for (int i=0; i<64; i++)                               // Message may be sensitive, clear message block.
      m_message_block[i] = 0;

    m_length_low  = 0;                                     // Clear message length.
    m_length_high = 0;                                     // Clear message length.
    m_computed    = true;

    for (int i=0; i<HASH_SIZE; i++) {
      m_final_digest[i] = m_intermediate_hash[i>>2] >> 8 * (3 - (i & 0x03));
      m_result += QString("%1").arg(m_final_digest[i], 2, 16, QLatin1Char('0'));
    }
  }
}

// This method accepts an array of octets as the next portion
// of the message.

void SHA1::hash(const QByteArray &data)
{
  unsigned int length = data.length();

  if (length <= 0)
    return; // Okay.

  if (m_computed) {
    m_corrupted = true;
    return; // Error.
  }

  if (m_corrupted) {
    qDebug() << "SHA1::hash(data) - corrupted context.";
    return; // Error.
  }

  for (unsigned int i=0; i<length; i++) {
    if (m_corrupted)
      break;

    m_message_block[m_message_block_index++] = (data[i] & 0xff);

    m_length_low += 8;
    if (m_length_low == 0) {
      m_length_high++;

      if (m_length_high == 0) {                            // Message is too long.
        m_corrupted = true;
      }
    }

    if (m_message_block_index == 64) {
      processMessageBlock();
    }
  }
}

// According to the standard, the message must be padded to an even
// 512 bits.  The first padding bit must be a '1'.  The last 64
// bits represent the length of the original message.  All bits in
// between should be 0.  This function will pad the message
// according to those rules by filling the Message_Block array
// accordingly.  It will also call the ProcessMessageBlock function
// provided appropriately.  When it returns, it can be assumed that
// the message digest has been computed.

void SHA1::padMessage()
{
  // Check to see if the current message block is too small to hold
  // the initial padding bits and length.  If so, we will pad the
  // block, process it, and then continue padding into a second
  // block.

  if (m_message_block_index > 55) {
    m_message_block[m_message_block_index++] = 0x80;
    while (m_message_block_index < 64) {
      m_message_block[m_message_block_index++] = 0;
    }

    processMessageBlock();

    while (m_message_block_index < 56) {
      m_message_block[m_message_block_index++] = 0;
    }
  }
  else {
    m_message_block[m_message_block_index++] = 0x80;
    while (m_message_block_index < 56) {
      m_message_block[m_message_block_index++] = 0;
    }
  }

  // Store the message length as the last 8 octets.

  m_message_block[56] = m_length_high >> 24;
  m_message_block[57] = m_length_high >> 16;
  m_message_block[58] = m_length_high >> 8;
  m_message_block[59] = m_length_high;
  m_message_block[60] = m_length_low >> 24;
  m_message_block[61] = m_length_low >> 16;
  m_message_block[62] = m_length_low >> 8;
  m_message_block[63] = m_length_low;

  processMessageBlock();
}

// This function will process the next 512 bits of the message
// stored in the Message_Block array.
//
// Comments:
// Many of the variable names in this code, especially the
// single character names, were used because those were the
// names used in the publication.

void SHA1::processMessageBlock()
{
  const quint32 K[] = {                                    // Constants defined in SHA-1.
                        0x5A827999,
                        0x6ED9EBA1,
                        0x8F1BBCDC,
                        0xCA62C1D6
                      };
  int           t;                                         // Loop counter.
  quint32       temp;                                      // Temporary word value.
  quint32       W[80];                                     // Word sequence.
  quint32       A, B, C, D, E;                             // Word buffers.

  // Initialize the first 16 words in the array W

  for (t=0; t<16; t++) {
    W[t]  = m_message_block[t * 4    ] << 24;
    W[t] |= m_message_block[t * 4 + 1] << 16;
    W[t] |= m_message_block[t * 4 + 2] << 8;
    W[t] |= m_message_block[t * 4 + 3];
  }

  for (t=16; t<80; t++) {
    W[t] = SHA1CircularShift(1, W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
  }

  A = m_intermediate_hash[0];
  B = m_intermediate_hash[1];
  C = m_intermediate_hash[2];
  D = m_intermediate_hash[3];
  E = m_intermediate_hash[4];

  for (t=0; t<20; t++) {
    temp = SHA1CircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
    E = D;
    D = C;
    C = SHA1CircularShift(30,B);
    B = A;
    A = temp;
  }

  for (t=20; t<40; t++) {
    temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
    E = D;
    D = C;
    C = SHA1CircularShift(30,B);
    B = A;
    A = temp;
  }

  for (t=40; t<60; t++) {
    temp = SHA1CircularShift(5,A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
    E = D;
    D = C;
    C = SHA1CircularShift(30,B);
    B = A;
    A = temp;
  }

  for (t=60; t<80; t++) {
    temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
    E = D;
    D = C;
    C = SHA1CircularShift(30,B);
    B = A;
    A = temp;
  }

  m_intermediate_hash[0] += A;
  m_intermediate_hash[1] += B;
  m_intermediate_hash[2] += C;
  m_intermediate_hash[3] += D;
  m_intermediate_hash[4] += E;

  m_message_block_index = 0;
}

