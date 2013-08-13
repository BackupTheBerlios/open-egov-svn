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

#include <QObject>
#include <QList>
#include <QString>
#include <QByteArray>

class MIDI : public QObject
{
  Q_OBJECT

  enum FileFormat {
    SingleTrack=0,                                         // Only one single track is in the file.
    MultipleTracksSynchronous=1,                           // Multiple tracks, which start all at the same time.
    MultipleTracksAsynchronous=2                           // Multiple tracks, can be completely asynchronous.
  };

  public:
    MIDI(QObject *parent = 0);
   ~MIDI();

    int loadFile(const QString &fileName);
    int parseData();

  protected:
    QByteArray  m_data;
    FileFormat  m_file_format;
    int         m_number_of_tracks;
    int         m_number_of_dtt;                           // Number of delta-time ticks per quarter note.
};

