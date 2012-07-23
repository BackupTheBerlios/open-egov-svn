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

#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>

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
    qWarning() << "Arguments:";
    qWarning() << " -f or --file-type: return readable name of file type";
    qWarning() << " -m or --mime-type: return mime type of file";
    qWarning() << " -v or --viewer: return viewer module for file";
    qWarning() << " -f or --file <file>: name of a file to look into";
    return 0;
  }

  QString fileName;
  QString argument;
  bool showFileType = false;
  bool showMimeType = false;
  bool showViewer   = false;

  if ((arguments.contains("-t")) || (arguments.contains("--file-type")))
    showFileType = true;
  if ((arguments.contains("-m")) || (arguments.contains("--mime-type")))
    showMimeType = true;
  if ((arguments.contains("-v")) || (arguments.contains("--viewer")))
    showViewer = true;

  qDebug() << "argument count: " << arguments.count();

  for (int i=0; i<arguments.count(); i++) {
      argument = arguments[i];
      //qDebug() << "arg " << i << " " << arguments[i];

      if (argument.startsWith('-')) {
        argument = argument.toLower();
        if (((argument == "--file") || (argument == "-f")) && (i+1 < arguments.count()))
          fileName = arguments[i+1];
      }
  }

  if (fileName.length() <= 0) {
    qDebug() << "No file name given.";
    return -2;
  }

  fileName  = QFileInfo(fileName).absoluteFilePath();

  qDebug() << "File: " << fileName;



  return 0;
}

