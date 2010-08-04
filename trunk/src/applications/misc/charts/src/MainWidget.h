// $Id$
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

#include <QAxBindable>
#include <QString>
#include <QTextEdit>
#include <QWidget>

class MainWidget : public QTextEdit, public QAxBindable
{
  Q_OBJECT

  Q_CLASSINFO("ClassID",        "{AC1E7EF3-E310-421f-BD97-8EE77F03F9CA}")
  Q_CLASSINFO("InterfaceID",    "{5676AA5A-B5D4-4412-B166-FF1A9D6DBD2D}")
  Q_CLASSINFO("EventsID",       "{D2AE041C-DEFE-4648-85E4-B2D59E25A31F}")
  Q_CLASSINFO("Version",        "1.0")
  Q_CLASSINFO("Description",    "Open eGovernment: Charts")
  Q_CLASSINFO("ToSuperClass",   "MainWidget")
  Q_CLASSINFO("StockEvents",    "yes")
  Q_CLASSINFO("Insertable",     "yes")           // Allows insertion into Microsoft Office apps.
  Q_CLASSINFO("RegisterObject", "yes")

  Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWidget(QWidget *parent = 0, const char *name = 0);

    void setTitle(const QString &title);
    QString title() const;

    QString m_title;
};

