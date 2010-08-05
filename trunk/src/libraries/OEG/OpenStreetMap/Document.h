// $Id: MapWidget.h 246 2010-08-04 18:58:33Z gerrit-albrecht $
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#pragma once

#include <OEG/Common.h>

#include <QObject>
#include <QList>
#include <QString>

namespace OEG { namespace OpenStreetMap {

class Changeset;
class Area;
class Node;
class Way;
class Relation;

class Document : public QObject
{
  Q_OBJECT

  public:
    Document(QObject *parent);
    ~Document();

    void loadFile();
    void saveFile();
    void loadFile(const QString &fileName);
    void saveFile(const QString &fileName);

  protected:
    QString toString();

  protected:
    QList<Changeset *>  m_changesets;
    QList<Node *>       m_nodes;
    QList<Way *>        m_ways;
    QList<Relation *>   m_relations;
};

}}

