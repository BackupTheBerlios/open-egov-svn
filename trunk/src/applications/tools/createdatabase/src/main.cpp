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
    qWarning() << "Can't open database file.";
    return 0;
  }

  QSqlQuery query(db);

  QDomDocument document("database");
  if (! document.setContent(&file)) {
    qWarning() << "Not a valid XML document.";
    return 0;
  }

  QDomElement root = document.documentElement();           // Get the root element.

  QString rootTag = root.tagName();                        // Check the root tag name.
  qDebug() << "root-Tag-Name: " << rootTag;

  QDomNodeList nodeList;
  QDomElement el;
  QStringList columns;

  nodeList = root.elementsByTagName("structures");         // We want to get the "structures"-Tag.
  if (nodeList.count() <= 0) {
    qWarning() << "No structures-Tag found.";
    return 0;
  }
  el = nodeList.at(0).toElement();
  qDebug() << "Using only the first Tag: " << el.tagName();

  QDomNodeList table_nodes, row_nodes;
  QDomElement  table_element, row_element;   // TODO: only one variable?
  QString      query_string, query_string_prefix;

  table_nodes = el.elementsByTagName("table");
  for(int i=0; i<table_nodes.count(); i++) {
    table_element = table_nodes.at(i).toElement();
    query_string  = "CREATE TABLE " + table_element.attribute("name") + " (";

    QDomNode entries = table_element.firstChild();
    columns.clear();

    while (! entries.isNull()) {
      QDomElement data = entries.toElement();
      QString s_tag = data.tagName();
      QString s_name, s_type, s_flags;
      QString s;

      s = "";
      s_name  = data.attribute("name");
      s_type  = data.attribute("type");
      s_flags = data.attribute("flags");

      if (s_type == "integer") {
        s = s_name + " INTEGER";

        if (s_flags.contains("primarykey", Qt::CaseInsensitive)) {
          s += " PRIMARY KEY";
        }
      }
      else if (s_type == "string") {
        s += s_name + " TEXT";
      }
      else {
        qWarning() << "Unknown column type. Will use TEXT.";
        s += s_name + " TEXT";
      }

      columns << s;
      entries = entries.nextSibling();
    }

    if (columns.count() > 0) {
      query_string += columns.join(", ");                    // Join the parameters to one comma-separated string.
    }
    else {
      qWarning() << "Found table with no columns.";
    }
    query_string += ")";

    qDebug() << "SQL: " << query_string;
    query.exec(query_string);
  }

  // https://www.sqlite.org/lang.html

  // query.exec("create table xyz (id int primary key, test int, loc varchar(20))");
  // query.exec("insert into xyz values(0, 1, \"tttt\")");
  // CREATE UNIQUE INDEX ggg ON table(id ASC)

  nodeList = root.elementsByTagName("data");               // We want to get the "data"-Tag.
  if (nodeList.count() <= 0) {
    qWarning() << "No data-Tag found.";
    return 0;
  }
  el = nodeList.at(0).toElement();
  qDebug() << "Using only the first Tag: " << el.tagName();

  table_nodes = el.elementsByTagName("table");
  for(int i=0; i<table_nodes.count(); i++) {
    table_element = table_nodes.at(i).toElement();
    query_string_prefix = "INSERT INTO " + table_element.attribute("name") + " VALUES (";

    row_nodes = table_element.elementsByTagName("row");
    for(int j=0; j<row_nodes.count(); j++) {
      row_element = row_nodes.at(j).toElement();

      columns.clear();
      QDomNode entries = row_element.firstChild();   // Loop through all field-Tags.
      while (! entries.isNull()) {
        QDomElement data = entries.toElement();
        QString s_tag = data.tagName();
        QString s_name;
        QString s;

        s_name = data.attribute("name");

        // TODO: Look at the datatype of the current column to decide how to format the value correctly.

        s = data.text().trimmed();
        if (s.isEmpty()) {
          s = "";
        }
        else if (QString::number(s.toInt()) == s) {           // Is integer, no '' needed.
        }
        else {
          s = "'" + s + "'";  // TODO: escaping
        }

        columns << s;
        entries = entries.nextSibling();
      }

      query_string = query_string_prefix;
      if (columns.count() > 0) {
        query_string += columns.join(", ");                    // Join the parameters to one comma-separated string.
      }
      else {
        qWarning() << "Found table with no columns.";
      }
      query_string += ")";

      qDebug() << "SQL: " << query_string;
      query.exec(query_string);
    }
  }

  return 0;
}

