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

#include <OEG/Common.h>

#include <QString>
#include <QTabWidget>
#include <QDebug>

class QKeyEvent;
class QMouseEvent;
class QToolButton;

namespace OEG { namespace Qt {

class TabWidget : public QTabWidget
{
  Q_OBJECT

  public:
    TabWidget(QWidget *parent = 0);
    ~TabWidget();

    void separateCloseTabButton(const QString &tooltip);

  public slots:
    void closeTab();

  signals:
    void mousePressed();
    void keyPressed();
    void mousePressedAtTabBar();
    void tabClicked(int index);

  protected:
    virtual void tabInserted(int index);
    virtual void tabRemoved(int index);
    virtual void tabLayoutChanged();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

    bool eventFilter(QObject *object, QEvent *event);

  private:
    QToolButton *m_close_tab_button;
};

}}

