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

#include <OEG/Common.h>
#include <OEG/Qt/Application.h>
#include <OEG/Crypt/AES.h>

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCryptographicHash>

#include "CRC32.h"
#include "Adler32.h"

int main(int argc, char *argv[])
{
  QCoreApplication app_core(argc, argv);
  QStringList arguments = QCoreApplication::arguments();
  QString programName = arguments.at(0);

  if (arguments.count() == 1) {
    qWarning() << "No args given.";
    return -1;
  }

  if ((arguments.contains("-h")) || (arguments.contains("--help"))) {
    qWarning() << "Call:";
    qWarning() << programName << "<filename>";
    return 0;
  }

  QString inputFileName;
  QString argument;

  for (int i=0; i<arguments.count(); i++) {
      argument = arguments[i];

      if (argument.startsWith('-')) {
        argument = argument.toLower();
        if (argument == "--md5")
          ;
      }
  }

  inputFileName = arguments[1];

  if (inputFileName.length() <= 0) {
    qDebug() << "No input file name given.";
    return -2;
  }

  inputFileName  = QFileInfo(inputFileName).absoluteFilePath();
  qDebug() << "File: " << inputFileName;

  QFile file(inputFileName);
  QByteArray result, input;
  int size;

  if (! file.open(QIODevice::ReadOnly)) {
    qDebug() << "File not found.";
    return -2;
  }

  size = file.size();
  //QDataStream in(&file);
  input = file.readAll();
  file.close();

  result = QCryptographicHash::hash(input, QCryptographicHash::Md4);
  qDebug() << "MD4" << result.toHex();
  result = QCryptographicHash::hash(input, QCryptographicHash::Md5);
  qDebug() << "MD5" << result.toHex();
  result = QCryptographicHash::hash(input, QCryptographicHash::Sha1);
  qDebug() << "SHA-1" << result.toHex();

  qDebug() << "Adler-32" << Adler32::calcHash(input);
  qDebug() << "CRC32" << CRC32::calcHash(input);

  return 0;
}

