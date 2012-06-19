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

#include <OEG/Qt/TabWidget.h>

#include <QString>
#include <QSplitter>

class QFileSystemModel;
class FolderView;

class FolderManager : public QSplitter
{
  Q_OBJECT

  public:
    FolderManager(QWidget *parent = 0);
    virtual ~FolderManager();

    void addFolderTabToActiveSide(const QString &path);
    OEG::Qt::TabWidget *currentTabWidget();

  protected:
    void addFolderTab(const QString &path, const bool left = true);
    inline bool activeView() const { return m_active_view_is_left; }
    void setActiveView(const bool activeView = true);
    FolderView *currentFolderView(const bool activeView = true);

  protected slots:
    void runCommand(const QString &name);

  protected slots:
    void tabWidgetCurrentChanged();
    void folderViewActivated();

  protected:
    OEG::Qt::TabWidget  *m_tabs_left;
    OEG::Qt::TabWidget  *m_tabs_right;
    bool                 m_active_view_is_left;
    QFileSystemModel    *m_file_system_model;
};

