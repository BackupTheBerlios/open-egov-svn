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

class QDockWidget;
class QMenuBar;
class QTabWidget;
class QTreeView;
class QTableWidget;
class QLabel;

class FilePlanEntry;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void createActions();
    virtual void createStatusBar();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createTabbedMenuBar();

  public slots:
    void loadFile();
    void saveFile();
    void updateStatusBar();

  private:
    QTabWidget             *m_tabs;
    QDockWidget            *m_dock_favorites;
    QList<FilePlanEntry *>  m_fileplan_list;
    QTableWidget           *m_fileplan;
    QWidget                *m_tab_fileplan;
    QWidget                *m_tab_search;
    QWidget                *m_tab_phonebook;
    QLabel                 *m_sb_pos;
};

