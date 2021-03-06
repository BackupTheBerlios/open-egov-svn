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
#include <QIcon>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>
#include <QVariantAnimation>
#include <QWidget>

#include <QObject>
#include <QString>

#include <QDebug>

namespace OEG { namespace Qt {

class TabbedMenuBarGroup : public QObject
{
  Q_OBJECT

  public:
    enum DisplayMode {
      TextAlways, TextOrIcon, IconAlways
    };

    enum StandardMenuBarTabs {
      File, Edit, Insert, PageLayout, View, Settings,  Help
    };

  public:
    TabbedMenuBarGroup(QObject *parent = 0);
    ~TabbedMenuBarGroup();

  public:
    inline QString title() const { return m_title; }
    inline void setTitle(const QString &title) { m_title = title; }

    inline unsigned int width() const { return m_width; }
    inline void setWidth(const unsigned int width) { m_width = width; }

    void addAction(const QAction *action, const QString &title);
    void showCommandButton();

  private:
    QString       m_title;
    unsigned int  m_width;
    bool          m_show_command_button;
};

}}

