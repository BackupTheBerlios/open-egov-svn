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

#include "MIDI.h"

#include <QApplication>
#include <QByteArray>
#include <QFile>

#include <QDebug>

#include <iostream>

MIDI::MIDI(QObject *parent /*=0*/)
 : QObject(parent)
{
}

MIDI::~MIDI()
{
}

int MIDI::loadFile(const QString &fileName)
{
  if (! QFile::exists(fileName)) {
    //
    return -1;
  }

  QFile file(fileName);
  if (! file.open(QIODevice::ReadOnly)) {
    //
    return -2;
  }

  m_data = file.readAll();

  file.close();

  if (m_data.size() <= 4) {
    std::cout << "Not enough data. size <= 4." << std::endl;
    return -3;
  }

  return parseData();
}

int MIDI::parseData()
{
  //qDebug() << "ddd";
  //qWarning() << "www";
  //std::cout << "ccc" << std::endl;

  int position = 0;
  QByteArray ba;

  if (! m_data.startsWith("MThd")) {                       // Header chunk always starts with: 4D 54 68 64.
    std::cout << "No header found." << std::endl;
    return -4;
  }
  position += 4;

  ba = m_data.mid(position, 4);                            // 4-byte size of the header is always: 00 00 00 06.
  position += 4;

  quint32 i = ba.data()[0];
  i = (i << 8) | ba.data()[1];
  i = (i << 8) | ba.data()[2];
  i = (i << 8) | ba.data()[3];

  if (i != 6) {                                            // Header size should be always 6.
    std::cout << "Wrong header size. Not 6." << std::endl;
    return -5;
  }

  ba = m_data.mid(position, 6);                            // Read the header.
  position += 6;

  i = ba.data()[0];                                        // 2 bytes: File format.
  i = (i << 8) | ba.data()[1];
  m_file_format = (MIDI::FileFormat) i;
  qDebug() << "File format:" << i;

  i = ba.data()[2];                                        // 2 bytes: Number of tracks in the midi file.
  i = (i << 8) | ba.data()[3];
  m_number_of_tracks = i;
  qDebug() << "Number of tracks:" << i;

  i = ba.data()[4];                                        // 2 bytes: Number of tracks in the midi file.
  i = (i << 8) | ba.data()[5];
  m_number_of_dtt = i;
  qDebug() << "Number of delta-time ticks:" << i;          // 2 bytes: Number of delta-time ticks per quarter note.
  qDebug() << " a:" << QByteArray::number(ba.data()[4], 16);
  qDebug() << " b:" << QByteArray::number(ba.data()[5], 16);
  if (i & 0x8000) {
    qDebug() << " top bit: 1";
	qDebug() << (0x7f00 & i);                              // 0111111100000000
	qDebug() << (0x00ff & i);
  }
  else {
    qDebug() << " top bit: 0";
  }

  // Parsing the tracks.

  while (position < m_data.size()) {
    ba = m_data.mid(position, 4);                          // Read the header.
    position += 4;
    if (ba != "MTrk") {                                    // Header chunk always starts with: 4D 54 72 6B
      std::cout << "No track header found." << std::endl;
      return -6;
    }

    ba = m_data.mid(position, 4);                          // 4-byte size of the header in bytes.
    position += 4;

    i = ba.data()[0];
    i = (i << 8) | ba.data()[1];
    i = (i << 8) | ba.data()[2];
    i = (i << 8) | ba.data()[3];
    qDebug() << "Track found with size:" << i;

	position += i;
  }

  std::cout << "Parsing finished. No errors." << std::endl;

  return 0;
}

