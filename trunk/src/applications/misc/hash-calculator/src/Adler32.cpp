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

//#include <OEG/Crypt/Adler32.h>

#include "Adler32.h"

Adler32::Adler32()
 : HashAlgorithm()
{
  m_hash_algorithm_name = "Adler-32";

  initialize(); // HashAlgorithm() ruft zwar initialize() auf, aber nur das Eigene!
}

Adler32::~Adler32()
{
}

void Adler32::initialize()
{
  HashAlgorithm::initialize();

  m_value = 1;
  m_a     = m_value & 0xffff;
  m_b     = (m_value >> 16) & 0xffff;
}

void Adler32::finalize()
{
  HashAlgorithm::finalize();

  m_value  = (m_b << 16) | m_a;
  m_result = QString("%1").arg(m_value, 0, 16);
}

QString Adler32::hash(const QByteArray &data)
{
  const int MODULO_PRIME_NUMBER = 65521;                   // Largest prime number less than 65536.

  for (int i=0; i<data.length(); i++) {
    m_a = (m_a + data[i]) % MODULO_PRIME_NUMBER;
    m_b = (m_b + m_a)     % MODULO_PRIME_NUMBER;
  }

  return result();
}

QString Adler32::calcHash(const QByteArray &data)
{
  Adler32 *ha = new Adler32();
  if (! ha)
    return "";
  qDebug() << "name" << ha->metaObject()->className();
  ha->hash(data);
  QString result = ha->result();
  delete ha;
  return result;
}

