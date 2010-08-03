// $Id$
//
// Open-eGovernment
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

#include <QList>
#include <QSplitter>
#include <QSplitterHandle>

class PointBar;
class SplitterHandleWidget;
class QLabel;

class SplitterHandle : public QSplitterHandle
{
  Q_OBJECT

  public:
    SplitterHandle(Qt::Orientation orientation, QSplitter *parent);
    virtual ~SplitterHandle();

    void setText(const QString &text);

    void addLabel(const QString &name);
    void addPointBar(const QString &name);

  protected:
    void setDefaultLayout();
    void deleteDefaultLayout();

  protected:
    QList<SplitterHandleWidget *>  m_widgets;
    QLabel                        *m_label;
};

