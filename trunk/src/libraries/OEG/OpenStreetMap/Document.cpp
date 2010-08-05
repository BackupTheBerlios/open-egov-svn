// $Id: MapWidget.cpp 246 2010-08-04 18:58:33Z gerrit-albrecht $
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

#include <OEG/OpenStreetMap/Document.h>

#include <QDebug>
#include <QList>
#include <QLatin1String>

#include "Changeset.h"
#include "Node.h"
#include "Way.h"
#include "Area.h"
#include "Relation.h"

using namespace OEG::OpenStreetMap;
using namespace Qt;

Document::Document(QObject *parent)
 : QObject(parent)
{
}

Document::~Document()
{
}

void Document::loadFile()
{
}

void Document::saveFile()
{
}

void Document::loadFile(const QString &fileName)
{
}

void Document::saveFile(const QString &fileName)
{
}

QString Document::toString()
{
  return "";
}

