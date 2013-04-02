// $Id:$
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

#include <QColor>
#include <QEvent>
#include <QIcon>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>
#include <QVariantAnimation>
#include <QWidget>

#include <QList>

#include <QDebug>

#include <OEG/Qt/TabbedMenuBarTab.h>

namespace OEG { namespace Qt {

// The TabbedMenuBar class implements a widget which combines the features of
// QMenu and QToolBar without being a Microsoft Ribbon. It looks like an improved QTabBar,
// but it's completely rewritten.
// Needed features: multi-selection, background colors, a bigger tab spacing, ...

class TabbedMenuBar : public QWidget
{
  Q_OBJECT

  public:
    TabbedMenuBar(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~TabbedMenuBar();

  public:
    TabbedMenuBarTab *tab(const QString &title);           // Finds or adds a register tab to the menubar.
    void removeTab(const QString &title);

    void loadFromXML(const QString &fileName);

  protected:
    void removeAllTabs();

  protected:
    QColor                     m_bg_color;                 // Background color.
    bool                       m_alternative_mode;
    QList<TabbedMenuBarTab *>  m_tabs;
    TabbedMenuBarTab           m_tab_template;
};

}}

