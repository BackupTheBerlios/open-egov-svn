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
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QHash>

#include <QDomDocument>
#include <QDomImplementation>
#include <QDomNodeList>
#include <QDomElement>

#include <QSqlDatabase>
#include <QSqlQuery>

QString escapeString(const QString &str)
{
  // Doubling the ' character is for SQLite. MySQL uses \' for escaping.
  return str.split("'").join("''");
}

void showParameters()
{
  qWarning("Parameters: --showSQL --verbose --target <XML file>");
}

void executeQuery(const QString &query)
{
}

int main(int argc, char *argv[])
{
  OEG::Qt::Application app(argc, argv, "createdatabase");
  QDir::setCurrent("db");

  QStringList args     = QCoreApplication::arguments();
  QString     fileName = "";
  bool        showSQL  = 0;
  bool        verbose  = 0;
  int         target   = 1;     // 1: SQLite, 2: MySQL, (later maybe 3: Oracle).

  foreach (const QString &arg, args) {
    if (arg.contains("--showSQL",  Qt::CaseInsensitive)) {
      showSQL = true;
    }
    else if (arg.contains("--verbose",  Qt::CaseInsensitive)) {
      verbose = true;
    }
    else if (arg.contains("--target",  Qt::CaseInsensitive)) {
      target = 2;
    }
    else if (arg.contains("--help",  Qt::CaseInsensitive)) {
      showParameters();
      return 0;
    }
  }

  if (argc <= 1) {
    qWarning("Create Database: No xml file given as parameter.");
    showParameters();

    //fileName = QFileDialog::getOpenFileName(0, "Create Database", QDir::currentPath(), _("XML Files (*.xml)"));
    //if (fileName.isEmpty())
    //  return 0;
    return -1;
  }
  else {
    fileName = args.last();
  }

  QFile file(fileName);
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning(_("File not open."));
    return 0;
  }

  if (verbose) {
    qDebug() << "Parameters:";
    qDebug() << "  showSQL"  << showSQL;
    qDebug() << "  target"   << target;
    qDebug() << "  fileName" << fileName;
  }

  QFileInfo fi(fileName);
  fileName = fi.completeBaseName() + ".db";
  if (verbose)
    qWarning(qPrintable(QString(_("Creating database: ")) + fileName.toLatin1()));

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(fileName);
  //db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=myaccessfile.mdb");
  if (! db.open()) {
    qWarning() << _("Can't open database file.");
    return 0;
  }

  QDomDocument document("database");
  if (! document.setContent(&file)) {
    qWarning() << _("Not a valid XML document.");
    return 0;
  }

  QDomElement root = document.documentElement();           // Get the root element.
  QString rootTag = root.tagName();                        // Check the root tag name.
  if (! rootTag.contains("database"))
    qDebug() << "root-Tag-Name: " << rootTag;

  QSqlQuery query(db);

  QDomNodeList nodes;
  QDomElement  el;
  QStringList  columns;

  nodes = root.elementsByTagName("structures");            // We want to get the "structures"-Tag.
  if (nodes.count() <= 0) {
    qWarning() << _("No structures tag found.");
    return 0;
  }
  el = nodes.at(0).toElement();
  //qDebug() << "Using only the first Tag: " << el.tagName();

  QDomNodeList table_nodes, row_nodes;
  QDomElement  element;
  QDomNode     entries;
  QString      query_string, query_string_prefix;
  QString      table_name;

  query_string = "PRAGMA foreign_keys = ON;";
  if (showSQL)
    qWarning() << _("SQL:") << query_string;
  if (! query.exec(query_string))
    qWarning() << _("Query failed:") << query_string;

  query_string = "PRAGMA foreign_keys;";
  if (showSQL)
    qWarning() << _("SQL:") << query_string;
  if (! query.exec(query_string))
    qWarning() << _("Query failed:") << query_string;
  query.next();
  qWarning() << "PRAGMA foreign_keys:" << query.value(0).toString();

  // Set "journal_mode" to in memory, journal isn't needed while creating the databases.

  query_string = "PRAGMA journal_mode = MEMORY;";
  if (showSQL)
    qWarning() << _("SQL:") << query_string;
  if (! query.exec(query_string))
    qWarning() << _("Query failed:") << query_string;

  query_string = "PRAGMA journal_mode;";
  if (showSQL)
    qWarning() << _("SQL:") << query_string;
  if (! query.exec(query_string))
    qWarning() << _("Query failed:") << query_string;
  query.next();
  qWarning() << "PRAGMA journal_mode:" << query.value(0).toString();

  QHash<QString, QString> column_datatypes;                // column_datatypes[tablename.tablecolumn] = "datatype"

  table_nodes = el.elementsByTagName("table");
  for(int i=0; i<table_nodes.count(); i++) {
    element = table_nodes.at(i).toElement();
    table_name = element.attribute("name");

    query_string = "DROP TABLE IF EXISTS " + table_name;
    if (showSQL)
      qWarning() << "SQL: " << query_string;
    if (! query.exec(query_string))
      qWarning() << "Query failed: " << query_string;

    //query.prepare("DROP TABLE IF EXISTS :tablename");
    //query.bindValue(":tablename", table_name);
    //if (! query.exec())
    //  qWarning() << "Query failed: " << query.lastQuery();
    //if (showSQL)
    //  qWarning() << "SQL: " << query.lastQuery();

    query_string  = "CREATE TABLE " + table_name + " (";

    columns.clear();                                       // We now fill this with the columns list for CREATE TABLE.

    entries = element.firstChild();
    while (! entries.isNull()) {
      QDomElement data = entries.toElement();
      QString s_tag = data.tagName();
      QString s_name, s_type, s_flags;
      QString s;

      if (s_tag == "column") {
        s = "";
        s_name  = data.attribute("name");                  // Column name.
        s_type  = data.attribute("type");                  // Column datatype as text string.
        s_flags = data.attribute("flags");                 // Flags for the column.

        column_datatypes[table_name + "." + s_name] = s_type; // Store datatype, so we can later use it again.

        if (s_type == "integer") {
          s = s_name + " INTEGER";

          if (s_flags.contains("primarykey", Qt::CaseInsensitive)) {
            s += " PRIMARY KEY";
            column_datatypes[table_name + "." + s_name] = "integer primary key";
          }
        }
        else if (s_type == "string") {
          s += s_name + " TEXT";
        }
        else if (s_type == "blob") {
          s += s_name + " BLOB";
        }
        else if (s_type == "date") {
          s += s_name + " TEXT";
        }
        else if (s_type == "numeric") {
          s += s_name + " NUMERIC";
        }
        else {
          qWarning() << "Unknown column type. Will use TEXT.";
          s += s_name + " TEXT";
        }

        columns << s;
      }
      else {
        // Else "<!-- -->" (s_tag == "") would add an empty column to the query!
        qDebug() << "Unknown or empty TAG (not column):" << s_tag << "(ignored).";
      }

      entries = entries.nextSibling();
    }

    if (columns.count() > 0) {
      query_string += columns.join(", ");                    // Join the parameters to one comma-separated string.
    }
    else {
      qWarning() << "Found table with no columns.";
    }
    query_string += ")";

    if (showSQL)
      qWarning() << "SQL: " << query_string;
    if (! query.exec(query_string))
      qWarning() << "Query failed: " << query_string;
  }

  // https://www.sqlite.org/lang.html

  // query.exec("create table xyz (id int primary key, test int, loc varchar(20))");
  // query.exec("insert into xyz values(0, 1, \"tttt\")");
  // CREATE UNIQUE INDEX ggg ON table(id ASC)

  nodes = root.elementsByTagName("data");                  // Get the "data"-tag.
  if (nodes.count() <= 0) {
    qWarning() << "No data-Tag found.";
    return 0;
  }
  el = nodes.at(0).toElement();
  //qDebug() << "Using only the first Tag: " << el.tagName();

  table_nodes = el.elementsByTagName("table");
  for(int i=0; i<table_nodes.count(); i++) {
    element = table_nodes.at(i).toElement();
    table_name = element.attribute("name");
    query_string_prefix = "INSERT INTO " + table_name + " VALUES (";

    row_nodes = element.elementsByTagName("row");
    for(int j=0; j<row_nodes.count(); j++) {
      element = row_nodes.at(j).toElement();               // row element.

      columns.clear();

      entries = element.firstChild();                      // Loop through all "field"-tags.
      while (! entries.isNull()) {
        QDomElement data = entries.toElement();
        QString s_tag = data.tagName();
        QString s_name;
        QString s;

        s_name = data.attribute("name");
        if (s_tag == "field") {
          s = data.text().trimmed();                       // Get the tag contents.

          if (s.isEmpty() && (column_datatypes[table_name + "." + s_name] == "string")) {
            s = "''";
          }
          else if (s.isEmpty()) {
            s = "NULL";
          }
          else if (column_datatypes[table_name + "." + s_name] == "integer primary key") {
            s = "NULL";
          }
          else if (column_datatypes[table_name + "." + s_name] == "string") {
            s = "'" + escapeString(s) + "'";
          }
          else if (column_datatypes[table_name + "." + s_name] == "date") {
            s = "'" + escapeString(s) + "'";
          }

          columns << s;
        }
        else {
          // Else "<!-- -->" (s_tag == "") would add an empty column to the query!
          qDebug() << "Unknown or empty TAG (not field):" << s_tag << "(ignored).";
        }

        entries = entries.nextSibling();
      }

      query_string = query_string_prefix;
      if (columns.count() > 0) {
        query_string += columns.join(", ");                    // Join the parameters to one comma-separated string.
      }
      else {
        qWarning() << _("Found table with no columns.");
      }
      query_string += ")";

      if (showSQL)
        qWarning() << _("SQL:") << query_string;
      if (! query.exec(query_string))
        qWarning() << _("Query failed:") << query_string;
    }
  }

  return 0;
}

