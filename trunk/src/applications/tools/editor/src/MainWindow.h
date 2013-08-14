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
#include <OEG/Qt/TabWidget.h>

#include <QList>
#include <QString>
#include <QLabel>
#include <QWidget>

class PluginInterface;
class TextEditor;

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
    virtual void createTabbedMenuBar() {};

  public slots:
    void standardActionClose();
    void standardActionOpen();
    void standardActionNew();
    void standardActionPrint();

  protected:
    TextEditor *currentEditor() const;

  protected slots:
    void updateStatusBar();

  private:
    void loadPlugins();
    void loadFileTypes();

  protected:
    OEG::Qt::TabWidget       *m_tabs;
    QList<PluginInterface *>  m_plugins;
    QLabel                   *m_sb_file_type;
    QLabel                   *m_sb_number_of_lines;
    QLabel                   *m_sb_current_row;
    QLabel                   *m_sb_current_column;
    QLabel                   *m_sb_overwrite_mode;
    QList<QObject *>          m_file_types;
    QString                   m_file_dialog_last_path;
};

