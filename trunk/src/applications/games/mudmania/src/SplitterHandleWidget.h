// $Id$
//
// Open-eGovernment
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

#include <QColor>
#include <QList>
#include <QString>
#include <QWidget>

class SplitterHandleWidget : public QWidget
{
  Q_OBJECT

  public:
    SplitterHandleWidget(QWidget *parent = 0);

    void enableForWorld(const QString &name);

  public slots:
    void newWorldActivated(const QString &name);

  protected:
    QList<QString>  m_world_names;

};

