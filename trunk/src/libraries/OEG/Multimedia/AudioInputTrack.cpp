// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <OEG/Multimedia/AudioInputTrack.h>

#include <QString>
#include <QAudioDeviceInfo>
#include <QAudioInput>

using namespace OEG::Multimedia;
using namespace Qt;

AudioInputTrack::AudioInputTrack(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_track_name  = "";
  m_active      = false;
  m_audio_input = 0;
}

AudioInputTrack::~AudioInputTrack()
{
  if (m_audio_input) {
    delete m_audio_input;
    m_audio_input = 0;
  }
}

void AudioInputTrack::setTrackName(const QString &trackName)
{
  m_track_name = trackName;
}

