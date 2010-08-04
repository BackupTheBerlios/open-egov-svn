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

#include <QWidget>

class QVBoxLayout;
class QMenuBar;
class QMenu;
class QAction;
class QCloseEvent;

class DesktopWidget : public QWidget //OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    DesktopWidget(QWidget *parent = 0);

  private slots:
    void actionProcessList();
    void about();
    void helpViewer();

  private:
    void createActions();
    void createMenus();

  protected:
    void closeEvent(QCloseEvent *event);

  protected:
    QVBoxLayout *m_layout;
    QMenuBar    *m_menubar;
    QMenu       *m_menu_file;
    QMenu       *m_menu_help;
    QAction     *m_action_exit;
    QAction     *m_action_help;
    QAction     *m_action_process_list;
    QAction     *m_action_about_app;
    QAction     *m_action_about_qt;
};

