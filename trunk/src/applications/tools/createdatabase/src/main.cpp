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

#include <OEG/Qt/Application.h>

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QStringList>

#include <QDomDocument>
#include <QDomImplementation>
#include <QDomNodeList>
#include <QDomElement>

#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
  QString fileName;
  QSqlQuery query;

  if (argc <= 1) {
    qWarning("Create Database: No xml file given as parameter.");

    fileName = QFileDialog::getOpenFileName(0, "Create Database", QDir::currentPath(), _("XML Files (*.xml)"));
    if (fileName.isEmpty())
      return 0;
  }
  else {
    fileName = argv[1];
  }

  OEG::Qt::Application app(argc, argv, "createdatabase");
  QDir::setCurrent("db");

  QFile file(fileName);
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return 0;
  }

  QFileInfo fi(fileName);
  fileName = fi.completeBaseName() + ".db";
  qWarning("Creating database: " + fileName.toAscii());

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(fileName);
  //db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=myaccessfile.mdb");
  if (! db.open()) {
    qWarning("Can't open database file.");
    return 0;
  }

  QDomDocument document("database");
  if (! document.setContent(&file)) {
    return 0;
  }

  QDomElement docElem = document.documentElement();    // Get the root element.

  QString rootTag = docElem.tagName(); // == persons     // Check the root tag name.
 
  // We want to get the "structures"-Tag.
  QDomNodeList nodeList = docElem.elementsByTagName("structures");

  QDomElement el;
  if (nodeList.count() <= 0) {
  }
  el = nodeList.at(0).toElement();
  qDebug() << "d1: " << el.tagName();

  QDomNodeList table_nodes   = el.elementsByTagName("table");
  QDomElement  table_element;
  QString      query_string;

  for(int i=0; i<table_nodes.count(); i++) {
    table_element = table_nodes.at(i).toElement();
    query_string  = "CREATE TABLE " + table_element.attribute("name") + " (";

    QDomNode entries = table_element.firstChild();
    QStringList sl;

    while (! entries.isNull()) {
      QDomElement data = entries.toElement();
      QString s_tag = data.tagName();
      QString s_name, s_type, s_flags;
      QString s;

      s_name  = data.attribute("name");
      s_type  = data.attribute("type");
      s_flags = data.attribute("type");

      if (s_type == "integer") {
        s = s_name " INTEGER";
      }


      // data.text();

      sl << s;
      entries = entries.nextSibling();
    }

 query_string += sl.sss(); //

    query_string += ")";
  }

  // https://www.sqlite.org/lang.html

  query.exec("create table xyz (id int primary key, test int, loc varchar(20))");
  query.exec("insert into xyz values(0, 1, \"tttt\")");
  // CREATE UNIQUE INDEX ggg ON table(id ASC)

  return 0;
}


