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

#include <QListWidget>
#include <QVBoxLayout>
#include <QAction>
#include <QtEvents>
#include <QMenu>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

#include <QtDebug>

#include "HistoryDockWidget.h"

HistoryDockWidget::HistoryDockWidget(QWidget *parent, Qt::WindowFlags flags)
 : QDockWidget(parent, flags)
{
  setObjectName("History Dock Widget");
  setWindowTitle(_("Search History"));

  //QFrame *swatch = new ColorDock(colorName, this);
  //swatch->setFrameStyle(QFrame::Box | QFrame::Sunken);
  //setWidget(swatch);
//setFrameStyle(QFrame::Box | QFrame::Sunken);

  m_context_menu = new QMenu("Menu", this);
  QAction *action = m_context_menu->addAction(_("Raise"));
  connect(action, SIGNAL(triggered()), this, SLOT(raise()));
  m_context_menu->addAction(action);
  m_context_menu->addSeparator();

  connect(m_context_menu, SIGNAL(aboutToShow()), this, SLOT(updateContextMenu()));

  m_list = new QListWidget(this);
  m_list->setSortingEnabled(false);
  m_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

  //QVBoxLayout *layout = new QVBoxLayout;
  //layout->addWidget(m_list);
  //setLayout(layout);
  setWidget(m_list);

  connect(m_list, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
          this,   SLOT(historyListItemDoubleClicked(QListWidgetItem *)));
}

void HistoryDockWidget::updateContextMenu()
{
}

void HistoryDockWidget::newHistoryEntry(const QString &s)
{
  QString value = s.trimmed();
  if (value.length() < 0)
    return;

  if (m_list)
    m_list->insertItem(0, value);
    //new QListWidgetItem(value, m_list);

  // remove some entries if needed ... TODO
}

void HistoryDockWidget::historyListItemDoubleClicked(QListWidgetItem *item)
{
  if (! item)
    return;

  emit queryDictionary(item->text());
}
