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

#include <QApplication>
#include <QFileInfo>
#include <QProcess>
#include <QSettings>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  app.setApplicationName("Screensaver Runner");
  app.setOrganizationName("G.A.S.I.");
  app.setOrganizationDomain("open-egov.de");

  // If the file extension is .scr, then it is replaced by .ini, else .ini
  // is attached to the end to create the file name of the settings file.

  QString iniFilePath;
  QFileInfo fi(QCoreApplication::applicationFilePath());
  QString suffix = fi.completeSuffix();
  if (suffix == "scr") {
    iniFilePath = QCoreApplication::applicationDirPath() + "/" + fi.baseName();
  }
  else {
    iniFilePath = QCoreApplication::applicationFilePath();
  }
  iniFilePath += ".ini";

  // Open settings file.

  QSettings settings(iniFilePath, QSettings::IniFormat);
  if (settings.status() != QSettings::NoError) {
    qDebug() << __FILE__ ": settings error: " << settings.status();
  }

  // The value of the oeg base directory is retrieved. Its bin directory contains the
  // screeensaver which should be started.

  QString oegPath;
  oegPath = settings.value("OEG-Directory", QLatin1String("I:\\Projekte\\berlios\\open-egov")).toString();
  if (oegPath.length() <= 0)
    return 0;

  QStringList args = QCoreApplication::arguments();

  if (! args.isEmpty())                       // Ignore the executable path name.
    args.removeFirst();

  for (int i = 0; i < args.size(); ++i) {
    args.replace(i, args.at(i).toLower());
    qDebug() << args.at(i).toLocal8Bit().constData();
  }

  args.removeDuplicates();

  QString exePath = oegPath + "/bin/" + fi.baseName();
  if (suffix == "scr")
    exePath += ".exe";
  if (! QFile::exists(exePath))
    return 0;

  QProcess process;
  process.setWorkingDirectory(oegPath + "/bin");
  process.startDetached(exePath, args);

  settings.setValue("OEG-Directory", oegPath);
  settings.setValue("LastArguments", args.join(" "));
  settings.setValue("LastScreenSaver", exePath);
  settings.sync();

  return 0;
}

