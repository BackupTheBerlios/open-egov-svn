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
#include <QList>
#include <QUrl>

class QAction;
class QMenuBar;
class QSplitter;
class QLabel;
class QWidget;
class QComboBox;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

  protected:
    virtual void createActions();
    virtual void createMenus();
    virtual void createToolBars();

  protected slots:
    void mapTypeCurrentIndexChanged(int index);

  private:
    QAction          *m_action_start;
    QAction          *m_action_stop;
    QComboBox        *m_map_type;
    QSplitter        *m_splitter;
    QLabel           *m_output;
};

