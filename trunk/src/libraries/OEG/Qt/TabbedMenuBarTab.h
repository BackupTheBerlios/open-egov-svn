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

#include <OEG/Qt/TabbedMenuBarGroup.h>

namespace OEG { namespace Qt {

class TabbedMenuBarTab : public QObject
{
  Q_OBJECT

  public:
    TabbedMenuBarTab(QObject *parent = 0);
    ~TabbedMenuBarTab();

    TabbedMenuBarGroup *group(const QString &title);
    void removeGroup(TabbedMenuBarGroup *group);

  protected:
    void removeAllGroups();

  protected:
    QString text;
    QString toolTip;
    QString whatsThis;
    QColor  selectedTextColor;
    QColor  selectedBackgroundColor;
    QColor  textColor;
    QColor  backgroundColor;

  private:
    QList<TabbedMenuBarGroup *>  m_groups;
};

}}

