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

#include <QColor>
#include <QDockWidget>
#include <QFrame>
#include <QLabel>
#include <QLatin1String>
#include <QMouseEvent>
#include <QPainter>
#include <QSettings>
#include <QTime>
#include <QTimer>
#include <QStyle>

#include "Widget.h"

Widget::Widget(QWidget *parent /*=0*/)
 : QWidget(parent), m_dock(0)
{
  m_diff_tl = QPoint(0, 0);
  m_diff_br = QPoint(0, 0);
  m_parent  = parent;

  m_label = new QLabel(this);
  if (! m_label)
    return;

  m_label->move(0, 0);
  m_label->setText("00:00:00");
  m_label->setFrameStyle(QFrame::Box | QFrame::Plain); // QFrame::Panel | QFrame::Sunken
  m_label->show();
  m_label->setStyleSheet("QLabel { background-color: yellow }");
  move(100, 100);
  resize(m_label->sizeHint());

  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
  m_timer->start(500);
}

Widget::~Widget()
{
  if (m_timer) {
    m_timer->stop();
    delete m_timer; m_timer = 0;
  }
}

void Widget::dockWidgetTopLevelChanged(bool topLevel)
{
  if (! m_dock)
    return;

  qDebug() << "Widget::dockWidgetTopLevelChanged TL=" << topLevel;
}

void Widget::updateDisplay()
{
  m_label->setText(QTime::currentTime().toString(Qt::TextDate));
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
  if ((event->modifiers() == Qt::ControlModifier) && (event->button() == Qt::LeftButton)) {
    QPoint pos;

    if (m_dock) {
      pos = this->mapToGlobal(this->pos());
      m_dock->hide();
      setParent(m_parent);
      move(m_parent->mapFromGlobal(pos));
      //resize(m_dock->widget()->size());
      show();
      delete m_dock; m_dock = 0;
    }
    else {
      pos = m_parent->mapToGlobal(this->pos());                      // Global coordinates of widget.
      m_dock = new QDockWidget(_("Clock"), m_parent);
      m_dock->setAllowedAreas(Qt::NoDockWidgetArea);
      setParent(m_dock);
      m_dock->setWidget(this);
      m_dock->setFloating(true);
      m_dock->setMinimumWidth(3);
      m_dock->setMinimumHeight(3);
      if (m_diff_tl.isNull()) {
        m_diff_tl = m_dock->geometry().topLeft() -                   // Difference is 4,22.
                    m_dock->frameGeometry().topLeft();
      }
      if (m_diff_br.isNull()) {
        m_diff_br = m_dock->frameGeometry().bottomRight() -
                    m_dock->geometry().bottomRight();
      }
      m_dock->move(m_parent->mapFromGlobal(pos) - m_diff_tl);
      m_dock->resize(size() + QSize(m_diff_tl.x() + m_diff_br.x(),
                                    m_diff_tl.y() + m_diff_br.y()));
      m_dock->show();
      //connect(m_dock, SIGNAL(topLevelChanged(bool)),
      //        this, SLOT(dockWidgetTopLevelChanged(bool)));
    }
  }
  else {
    QWidget::mouseDoubleClickEvent(event);
  }
}

void Widget::closeEvent(QCloseEvent *event)
{

  event->accept();
}

