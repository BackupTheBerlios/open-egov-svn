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

#include <OEG/Multimedia/AudioOutput.h>

#include <QString>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QIODevice>
#include <QFile>

using namespace OEG::Multimedia;
using namespace Qt;

AudioOutput::AudioOutput(QObject *parent /*=0*/)
 : QObject(parent), m_audio_output(0)
{
  QAudioFormat format;
  format.setSampleSize(16);
  format.setSampleRate(44100);
  format.setChannelCount(2);
  format.setCodec("audio/pcm");
  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setSampleType(QAudioFormat::SignedInt);

  //qWarning() << "available output devices:" << QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
  foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    qWarning() << "available device (name only): " << deviceInfo.deviceName();
  qWarning() << "default output device:" << QAudioDeviceInfo::defaultOutputDevice().deviceName();

  QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
  if (! device.isFormatSupported(format)) {
    qWarning() << "Default format not supported - trying to use nearest";
    format = device.nearestFormat(format);
  }

  QIODevice *output_io_device;
  Q_UNUSED(output_io_device)

  m_audio_output = new QAudioOutput(device, format, this);

  connect(m_audio_output, SIGNAL(notify()),
                          SLOT(notified()));
  connect(m_audio_output, SIGNAL(stateChanged(QAudio::State)),
                          SLOT(handleStateChanged(QAudio::State)));
}

AudioOutput::~AudioOutput()
{
  if (m_audio_output) {
    delete m_audio_output;
    m_audio_output = 0;
  }
}

void AudioOutput::readWAV(const QString &fileName)
{
  QFile file(fileName);                                    // Or from ":/sounds/xxx.wav"
  qDebug() << file.open(QIODevice::ReadOnly);
  file.seek(44);                                           // Skip wav header.



  file.close();
}

void AudioOutput::notified()
{
  qWarning() << "bytesFree = " << m_audio_output->bytesFree() << ", "
             << "elapsedUSecs = " << m_audio_output->elapsedUSecs() << ", "
             << "processedUSecs = " << m_audio_output->processedUSecs();
}

void AudioOutput::handleStateChanged(QAudio::State state)
{
  qWarning() << "state = " << state;
}

