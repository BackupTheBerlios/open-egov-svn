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

#include <OEG/Qt/Application.h>

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QHash>
#include <QApplication>

#include <QDomDocument>
#include <QDomImplementation>
#include <QDomNodeList>
#include <QDomElement>

QString     application_binary  = "";
QString     application_name    = "";
QString     application_version = "";
QString     pro_qt              = "";
QString     pro_packages        = "";
QString     pro_config          = "";
QString     mainwindow_class    = "";

int copyFileAndReplacePlaceholders(const QString &inputFileName, const QString &outputFileName)
{
  QFile inputFile(inputFileName);

  if (! inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning("Input template file not open.");
    return -1;
  }

  QFile outputFile(outputFileName);
  if (! outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning("Output file not open.");
    return -2;
  }

  QTextStream in(&inputFile);
  QTextStream out(&outputFile);

  while (! in.atEnd()) {
    QString line = in.readLine();

    if (line.contains("$$CURRENT-YEAR$$", Qt::CaseInsensitive)) {
      line.replace("$$CURRENT-YEAR$$", QString::number(QDate::currentDate().year()),
                   Qt::CaseInsensitive);
    }
    if (line.contains("$$APPLICATION-VERSION-CSV$$", Qt::CaseInsensitive)) {
      line.replace("$$APPLICATION-VERSION-CSV$$",
                   application_version.split(".").join(","),
                   Qt::CaseInsensitive);
    }
    if (line.contains("$$APPLICATION-VERSION$$", Qt::CaseInsensitive)) {
      line.replace("$$APPLICATION-VERSION$$", application_version,
                   Qt::CaseInsensitive);
    }
    if (line.contains("$$APPLICATION-BINARY$$", Qt::CaseInsensitive)) {
      line.replace("$$APPLICATION-BINARY$$", application_binary, Qt::CaseInsensitive);
    }
    if (line.contains("$$APPLICATION-NAME$$", Qt::CaseInsensitive)) {
      line.replace("$$APPLICATION-NAME$$", application_name, Qt::CaseInsensitive);
    }
    if (line.contains("$$MAINWINDOW-CLASS$$", Qt::CaseInsensitive)) {
      line.replace("$$MAINWINDOW-CLASS$$", mainwindow_class, Qt::CaseInsensitive);
    }

    out << line << "\n";
  }

  outputFile.close();
  inputFile.close();

  return 0;
}

int updateFileAndReplaceHeader(const QString &inputFileName, const QString &sourceFileName)
{
  QFile inputFile(inputFileName);

  if (! inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning("Input template file not open.");
    return -1;
  }





  inputFile.close();

  return 0;
}

QString templatesFileName(const QString &relativeTemplatesFileName)
{
  return QCoreApplication::applicationDirPath() + QDir::separator() +
         ".." + QDir::separator() + "/src/templates/" + relativeTemplatesFileName;
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QStringList args                = QCoreApplication::arguments();
  QString     filename            = "";
  bool        verbose             = false;

  bool        generate_pro        = false;                 // Data from application.xml
  bool        generate_main       = false;
  bool        generate_rc         = false;
  bool        update_files        = false;                 // Only via command line, not needed in xml.

  application_binary  = "";
  application_name    = "";
  application_version = "";
  pro_qt              = "";
  pro_packages        = "";
  pro_config          = "";
  mainwindow_class    = "MainWindow";                      // <data name="mainwindow-class" value="" />

  foreach (const QString &arg, args) {
    if (arg.contains("--verbose", Qt::CaseInsensitive)) {
      verbose = true;
    }
    if (arg.contains("--update-files", Qt::CaseInsensitive)) {
      update_files = true;
    }
  }

  if (argc <= 1) {
    qWarning("Create Sources: No xml file given as parameter.");
    qWarning("Parameters: [--verbose] <XML file>");

    filename = "application.xml";
  }
  else {
    filename = args.last();
  }

  if (! QFile::exists(filename)) {
    qWarning("File does not exist.");

    filename = QFileDialog::getOpenFileName(0, _("Select the XML instruction file"), QDir::currentPath(), _("XML Files (*.xml)"));
    if (filename.isEmpty())
      return 0;

    if (! QFile::exists(filename))
      return -1;
  }

  QFile file(filename);
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning("File not open.");
    return -2;
  }

  if (verbose) {
    qDebug() << "Parameters:";
    qDebug() << "  filename" << filename;
    qDebug() << "  update files" << update_files;
  }

  // Parse XML file.

  QDomDocument document("application");
  if (! document.setContent(&file)) {
    qWarning() << "Not a valid XML document.";
    return 0;
  }

  QDomElement root = document.documentElement();           // Get the root element.
  QString rootTag = root.tagName();                        // Check the root tag name.
  if (! rootTag.contains("application"))
    qDebug() << "Wrong root tag name:" << rootTag;

  // Ready to find our data.

  QDomNodeList nodes;
  QDomElement  element;
  QDomNode     entries;
  QString      s;

  // Automatically set application binary from the XML application tag if attribute if present.

  if (element.hasAttribute("base")) {
    s = element.attribute("base");
    if (s.length() > 0)
      application_binary = s;
  }

  // Find project tag.

  nodes = root.elementsByTagName("project");               // We want to get the "project" tag.
  if (nodes.count() <= 0) {
    qWarning() << "No project tag found.";
    return 0;
  }
  element = nodes.at(0).toElement();
  qDebug() << "Using only the first tag:" << element.tagName();

  // Parse the data tags inside of the project tag.

  entries = element.firstChild();
  while (! entries.isNull()) {
    QDomElement data = entries.toElement();

    if (data.tagName() != "data")                          // Unknown tag or comment (<!-- --> is an empty tag).
      continue;

    QString attr_name  = data.attribute("name");           // Parse entry, every data tag cotains
    QString attr_value = data.attribute("value");          // a name and value pair of attributes.

    if (attr_name == "application-binary") {
      application_binary = attr_value;           // TODO: check.
    }
    else if (attr_name == "application-name") {
      application_name = attr_value;             // TODO: check.
    }
    else if (attr_name == "application-version") {
      application_version = attr_value;          // TODO: check.
    }
    else if (attr_name == "generate-pro") {
      generate_pro = (attr_value == "true") ? true : false;
    }
    else if (attr_name == "generate-main") {
      generate_main = (attr_value == "true") ? true : false;
    }
    else if (attr_name == "generate-rc") {
      generate_rc = (attr_value == "true") ? true : false;
    }
    else if (attr_name == "pro-qt") {
      pro_qt = attr_value;                       // TODO: check.
    }
    else if (attr_name == "pro-packages") {
      pro_packages = attr_value;                 // TODO: check.
    }
    else if (attr_name == "pro-config") {
      pro_config = attr_value;                   // TODO: check.
    }
    else if (attr_name == "mainwindow-class") {
      mainwindow_class = attr_value;             // TODO: check.
    }

    entries = entries.nextSibling();
  }

  file.close();

  // Now generate files.

  QFileInfo fi(filename);
  QString srcDirName = fi.canonicalPath() + QDir::separator() + "src" + QDir::separator();

  if (generate_pro) {
    filename = srcDirName + "src.pro";
    if (verbose)
      qWarning() << "Creating pro file:" << filename;

    file.setFileName(filename);
    if (! file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qWarning("Output file not open.");
      return -3;
    }

    QTextStream out(&file);
    out << "# $Id" << ":$\n";
    out << "#\n";
    out << "# Automatically generated file. Do not edit manually!\n";
    out << "# See application.xml in parent directory (project tag).\n";
    out << "# This file is part of the Open E-Government project.\n";
    out << "\n";
    out << "TARGET    = " << application_binary << "\n";
    out << "SOURCES   = *.cpp\n";

    QDir dir;
    dir = fi.dir();
    dir.cd("src");
    dir.setNameFilters(QStringList() << "*.h");
    dir.setFilter(QDir::Files);
    if (dir.entryList().count() > 0)
      out << "HEADERS   = *.h\n";
    else
      out << "HEADERS   = \n";

    out << "FORMS     = ";
    if (dir.cd("forms")) {
      dir.setNameFilters(QStringList() << "*.ui");
      if (dir.entryList().count() > 0)
        out << "forms/*.ui";
      dir.cdUp();
    }
    out << "\n";

    out << "QT       += " << pro_qt << "\n";
    out << "CONFIG   += " << pro_config << "\n";
    out << "PACKAGES  = " << pro_packages << "\n";
    out << "\n";
    out << "include(../../../common.pri)" << "\n";
    out << "\n";

    file.close();
  }

  if (generate_main) {
    filename = srcDirName + "main.cpp";
    if (verbose)
      qWarning() << "Creating standard main file:" << filename;

    copyFileAndReplacePlaceholders(templatesFileName("main.cpp"), filename);
  }

  if (generate_rc) {
    filename = srcDirName + "application.rc";
    if (verbose)
      qWarning() << "Creating rc file:" << filename;

    copyFileAndReplacePlaceholders(templatesFileName("application.rc"), filename);
  }

  if (update_files) {
    QDir dir;

    dir = fi.dir();
    dir.cd("src");
    dir.setNameFilters(QStringList() << "*.cpp" << "*.h");
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    foreach (QString fn, dir.entryList()) {
      qDebug() << "Updating:" << fn;

      updateFileAndReplaceHeader(templatesFileName("source-file-header.txt"), fn);
    }
  }

  return 0;
}

