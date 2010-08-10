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

#include <QDebug>
#include <QPoint>
#include <QString>
#include <QWidget>

class QDockWidget;
class QMouseEvent;
class QLabel;
class QTimer;

class Widget : public QWidget
{
  Q_OBJECT

  public:
    Widget(QWidget *parent = 0);
    virtual ~Widget();

  public slots:
    void dockWidgetTopLevelChanged(bool topLevel);
    void updateDisplay();

  signals:
    void removePlugin(QWidget *pluginInterface);

  protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);

  protected:
    QTimer      *m_timer;
    QLabel      *m_label;
    QWidget     *m_parent;
    QDockWidget *m_dock;
    QPoint       m_diff;                 // Difference between pos of dock frame and its inner widget.
};

