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

#include <OEG/Qt/TabWidget.h>

#include <QToolButton>
#include <QIcon>
#include <QStyle>
#include <QStyleOption>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>

using namespace OEG::Qt;
using namespace Qt;

TabWidget::TabWidget(QWidget *parent /*=0*/)
 : QTabWidget(parent)
{
  m_close_tab_button = 0;

  tabBar()->installEventFilter(this);
}

TabWidget::~TabWidget()
{
  if (m_close_tab_button) {
    delete m_close_tab_button; m_close_tab_button = 0;
  }
}

void TabWidget::closeTab()
{
  QWidget *page = currentWidget();

  if (! page)
    return;

  removeTab(currentIndex());

  delete page;
}

void TabWidget::separateCloseTabButton(const QString &tooltip)
{
  int s = height() - (style()->pixelMetric(QStyle::PM_TabBarTabVSpace) +
                      style()->pixelMetric(QStyle::PM_TabBarBaseHeight));

  m_close_tab_button = new QToolButton(this);
  if (! m_close_tab_button)
    return;
  m_close_tab_button->setFixedSize(20, 20);
  m_close_tab_button->setAutoRaise(true);
  m_close_tab_button->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
  m_close_tab_button->setToolTip(tooltip);
  m_close_tab_button->setStatusTip(tooltip);
  setCornerWidget(m_close_tab_button);

  connect(m_close_tab_button, SIGNAL(clicked()),
          this,               SLOT(closeTab()));
}

// This function was missed in QTabWidget, only available in QTabBar.

void TabWidget::tabLayoutChanged()
{
  if (m_close_tab_button) {
    if (count() > 0) {
      m_close_tab_button->show();
    }
    else {
      m_close_tab_button->hide();
    }
  }
}

void TabWidget::tabInserted(int index)
{
  Q_UNUSED(index);

  QTabWidget::tabInserted(index);

  tabLayoutChanged();
}

void TabWidget::tabRemoved(int index)
{
  QTabWidget::tabRemoved(index);

  tabLayoutChanged();
}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
  emit mousePressed();

  int clickedItem = -1;
  for (int i=0; i<tabBar()->count(); i++) {
    if (tabBar()->tabRect(i).contains(event->pos())) {
      clickedItem = i;
      break;
    }
  }
  if (clickedItem > -1)
    emit tabClicked(clickedItem);

  qDebug() << "TabWidget::mousePressEvent" << clickedItem;

  QTabWidget::mousePressEvent(event);
}

void TabWidget::keyPressEvent(QKeyEvent *event)
{
  emit keyPressed();

  QTabWidget::keyPressEvent(event);
}

bool TabWidget::eventFilter(QObject *object, QEvent *event)
{
  if (object == tabBar() && event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    //removeTab(tabBar()->tabAt(mouseEvent->pos()));
    emit mousePressedAtTabBar();
    //return true;
  }

  return QTabWidget::eventFilter(object, event);
}

