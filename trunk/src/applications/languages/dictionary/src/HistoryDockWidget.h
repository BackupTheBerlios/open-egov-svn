// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <OEG/Qt/Application.h>

#include <QDockWidget>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QActionGroup)
QT_FORWARD_DECLARE_CLASS(QListWidget)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QListWidgetItem)

class HistoryDockWidget : public QDockWidget
{
  Q_OBJECT

  public:
    HistoryDockWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  protected:
    //virtual void contextMenuEvent(QContextMenuEvent *event);

  signals:
    void queryDictionary(const QString &value);

  private slots:
    void updateContextMenu();

  public slots:
    void newHistoryEntry(const QString &s);
    void historyListItemDoubleClicked(QListWidgetItem *item);

  protected:
    QListWidget *m_list;
    QMenu       *m_context_menu;
};

