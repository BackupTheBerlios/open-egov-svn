// $Id$
//
// Open-eGovernment
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

#include <OEG/Common.h>

#include <QApplication>
#include <QLatin1String>
#include <QGradient>
#include <QGridLayout>
#include <QIcon>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QProgressBar>

#include "SplitterHandlePointBar.h"
#include "SplitterHandleLabel.h"
#include "SplitterHandle.h"

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *parent)
 : QSplitterHandle(orientation, parent)
{
  m_label = new QLabel(this);
  m_label->setText("");
  m_label->setCursor(Qt::ArrowCursor);
  m_label->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  setDefaultLayout();
}

SplitterHandle::~SplitterHandle()
{
  while (! m_widgets.isEmpty())
    delete m_widgets.takeFirst();
}

void SplitterHandle::setText(const QString &text)
{
  m_label->setText(text);
}

void SplitterHandle::addLabel(const QString &name)
{
  SplitterHandleLabel *label = new SplitterHandleLabel(this);

  m_widgets.append(label);
}

void SplitterHandle::addPointBar(const QString &name)
{
  SplitterHandlePointBar *bar = new SplitterHandlePointBar(this);

  m_widgets.append(bar);
}

void SplitterHandle::setDefaultLayout()
{
  deleteDefaultLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_label);
  setLayout(layout);
}

void SplitterHandle::deleteDefaultLayout()
{
  if (layout() > 0)
    delete layout();
}

