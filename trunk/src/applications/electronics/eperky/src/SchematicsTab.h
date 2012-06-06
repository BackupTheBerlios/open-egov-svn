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

#pragma once

#include <QFrame>
#include <QString>

class QWidget;
class QGraphicsView;

class SchematicsScene;

class SchematicsTab : public QFrame
{
  Q_OBJECT

  public:
    SchematicsTab(QWidget *parent = 0);
    virtual ~SchematicsTab();

    inline SchematicsScene *scene() const { return m_scene; }
    inline QGraphicsView   *view()  const { return m_view;  }

  protected:
    SchematicsScene *m_scene;
    QGraphicsView   *m_view;
};

