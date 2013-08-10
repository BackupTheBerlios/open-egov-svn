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
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QSettings>
#include <QString>
#include <QStringList>

#include <QDomDocument>
#include <QDomImplementation>
#include <QDomNodeList>
#include <QDomElement>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  QStringList arguments = QCoreApplication::arguments();
  QString programName = arguments.at(0);

 QDir::setCurrent("data/file-identifier");

  if (arguments.count() == 1) {
    qWarning() << _("No args given.");
    return -1;
  }

  if ((arguments.contains("-h")) || (arguments.contains("--help"))) {
    qWarning() << _("Arguments:");
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

  qDebug() << "File:" << fileName;

  // Read data/file-identifier/filetypes.xml.

  QFile file(fileName);
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning(_("File not open."));
    return 0;
  }

  QDomDocument document("filetypes");
  if (! document.setContent(&file)) {
    qWarning() << _("Not a valid XML document.");
    return 0;
  }

  QDomElement root = document.documentElement();           // Get the root element.
  QString rootTag = root.tagName();                        // Check the root tag name.
  if (! rootTag.contains("filetypes"))
    qDebug() << "root-Tag-Name: " << rootTag;

  QDomNodeList nodes;
  QDomElement el;
  QStringList searchpatterns;

  nodes = root.elementsByTagName("searchpatterns");        // We want to get the "searchpatterns"-Tag.
  if (nodes.count() <= 0) {
    qWarning() << _("No searchpatterns-Tag found.");
    return -3;
  }
  el = nodes.at(0).toElement();
  qDebug() << _("Using only the first Tag:") << el.tagName();

  QDomNodeList table_nodes, row_nodes;
  QDomElement  element;
  QDomNode     entries;


  return 0;
}

