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

#include <QList>

#include "PluginInterface.h"

class QVBoxLayout;
class QMenuBar;
class QMenu;
class QAction;
class QCloseEvent;
class QWidget;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  private slots:
    void actionProcessList();

  private:
    void createActions();
    void createMenus();
    void loadPlugins();

  protected:
    void closeEvent(QCloseEvent *event);

  protected:
    QList<PluginInterface *> m_plugins;

    QVBoxLayout *m_layout;
    QMenuBar    *m_menubar;
    QMenu       *m_menu_file;
    QMenu       *m_menu_help;
    QAction     *m_action_process_list;
};

