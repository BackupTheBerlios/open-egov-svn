// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <QMainWindow>
#include <QModelIndex>
#include <QString>
#include <QList>
#include <QWidget>

class QDockWidget;
class QMenuBar;
class QTabWidget;
class QTreeView;

class ButtonsDockWidget;
class FileSystemModel;
class FolderView;

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

    FolderView *currentFolderView();

  protected:
    void runCommand(const QString &name);
    void removeColumnsFromTree();

  protected slots:
    void viewCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void treeActivated(const QModelIndex &index);
    void treeCollapsed(const QModelIndex &index);
    void treeExpanded(const QModelIndex &index);
    void updateFileSystemViews();
    void directoryLoaded(const QString &path);

    void tabCurrentChanged(int index);
    void tabCloseRequested(int index);

  private:
    OEG::Qt::TabWidget  *m_tabs;
    QDockWidget         *m_dock_tree;
    QTreeView           *m_dock_tree_view;
    ButtonsDockWidget   *m_dock_buttons;
    QDockWidget         *m_dock_preview;
};

