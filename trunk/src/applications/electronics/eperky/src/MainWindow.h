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

#include <OEG/Qt/MainWindow.h>

#include <QString>
#include <QWidget>
#include <QList>

#include "PluginInterface.h"

class QTabWidget;
class QTextEdit;

class SchematicsScene;
class SchematicsTab;

class OEG::Qt::ToolProvider;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createToolProvider() {};

  private:
    void loadPlugins();

  protected:
    QTabWidget               *m_tabs;
    QWidget                  *m_tab_project;
    QWidget                  *m_tab_part_list;
    SchematicsTab            *m_tab_schematics;
    QWidget                  *m_tab_pcb_layout;
    QWidget                  *m_tab_simulation;
    QTextEdit                *m_tab_notes;

    QList<PluginInterface *>  m_plugins;
};

