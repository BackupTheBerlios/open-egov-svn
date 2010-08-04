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

#include <OEG/Qt/MainWindow.h>

#include <QList>
#include <QString>
#include <QWidget>

class QAction;
class QLabel;
class QTabWidget;
class QTimer;

namespace OEG { namespace GIS {
  class MapWidget;
}}

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void createActions();
    virtual void createStatusBar();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createToolProvider() {};

  public slots:
    void receiveCoordinatesAtMouse(double x, double y);

  protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

  protected:
    OEG::GIS::MapWidget *m_map;
    QLabel              *m_coordinates;
};

