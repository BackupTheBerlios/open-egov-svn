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
#include <QFileInfo>
#include <QByteArray>
#include <QDebug>

//#include <OEG/Crypt/HashAlgorithm.h>

#include "HashAlgorithm.h"

HashAlgorithm::HashAlgorithm()
{
  m_hash_algorithm_name = "";

  initialize(); // Needed? Called twice!
}

HashAlgorithm::HashAlgorithm(const HashAlgorithm &ha)
{
}

HashAlgorithm::~HashAlgorithm()
{
}

void HashAlgorithm::hash(const QString &fileName)
{
  QString inputFileName = QFileInfo(fileName).absoluteFilePath();
  qDebug() << "File:" << inputFileName;

  QFile file(inputFileName);

  hash(file);
}

void HashAlgorithm::hash(QFile &file)
{
  QByteArray input;
  int size;

  if (! file.open(QIODevice::ReadOnly)) {
    qDebug() << "File not found.";
    return;
  }

  size = file.size();
  input = file.readAll();  // TODO: read chunks and progress them with indicator.
  file.close();

  hash(input);
}

void HashAlgorithm::initialize()
{
  m_finalized = false;
  m_value     = 0;
  m_result    = "";
}

void HashAlgorithm::finalize()
{
  m_finalized = true;
}

QString HashAlgorithm::result()
{
  if (! m_finalized) {
    finalize();
  }

  return m_result;
}

QString HashAlgorithm::hashAlgorithmName() const
{
  return m_hash_algorithm_name;
}

