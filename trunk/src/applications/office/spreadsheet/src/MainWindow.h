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

#include <OEG/Common.h>
#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/TabWidget.h>

#include "DocumentProperties.h"
#include "Settings.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class CellTable;
class PropertiesDock;
class FunctionsDock;
class QTableWidgetItem;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow();

  protected slots:
    void action_file_load();
    void action_file_save();
    void action_file_save_as();
    void action_file_close();
    void action_file_page_setup();
    void action_file_print();
    void action_file_print_preview();
    void action_file_properties();

    void action_view_dock_functions();
    void action_view_dock_properties();

    void action_insert_rows();
    void action_insert_columns();
    void action_insert_sheet();
    void action_insert_diagram();

    void action_settings_common();
    void action_settings_document();
    void action_settings_security();
    void action_settings_view();

    void createActions();
    void createMenus();
    void createToolBars();

    void tabWidgetTitleDoubleClicked(int index);
    void tabWidgetContextMenu(const QPoint &pos);
    void tableCellClicked(int row, int column);
    void tableItemClicked(QTableWidgetItem *item);

  protected:
    void loadDocument(const QString &filename);
    void saveDocument(const QString &filename);
    void clearDocument();

    void setCurrentFilename(const QString &filename);

  protected:
    QMenu               *m_menu_file;
    QMenu               *m_menu_edit;
    QMenu               *m_menu_view;
    QMenu               *m_menu_view_toolbars;
    QMenu               *m_menu_view_docks;
    QMenu               *m_menu_insert;
    QMenu               *m_menu_settings;
    QMenu               *m_menu_help;

    QAction             *m_action_insert_rows;
    QAction             *m_action_insert_columns;
    QAction             *m_action_insert_sheet;
    QAction             *m_action_insert_diagram;

    QAction             *m_action_file_properties;

    QAction             *m_action_view_toolbar_edit;
    QAction             *m_action_view_toolbar_format;
    QAction             *m_action_view_toolbar_widgets;
    QAction             *m_action_view_toolbar_file;
    QAction             *m_action_view_statusbar;
    QAction             *m_action_view_dock_functions;
    QAction             *m_action_view_dock_properties;
    QAction             *m_action_view_full_screen;
    QAction             *m_action_view_zoom;

    QAction             *m_action_settings_common;
    QAction             *m_action_settings_document;
    QAction             *m_action_settings_security;
    QAction             *m_action_settings_view;

    OEG::Qt::TabWidget  *m_tabs;
    QToolBar            *m_toolbar_edit;
    QToolBar            *m_toolbar_format;
    QToolBar            *m_toolbar_widgets;
    QToolBar            *m_toolbar_file;
    FunctionsDock       *m_dock_functions;
    PropertiesDock      *m_dock_properties;
    DocumentProperties   m_properties;
    Settings             m_settings;
};

