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

#include <QColor>
#include <QLabel>
#include <QLatin1String>
#include <QMouseEvent>
#include <QPainter>
#include <QSettings>
#include <QTime>
#include <QStyle>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "GraphicsItem.h"

GraphicsItem::GraphicsItem(QGraphicsItem *parent /*=0*/)
 : QGraphicsItem(parent)
{
  setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
  setAcceptDrops(true);

  m_mouse_pressed = false;
}

GraphicsItem::~GraphicsItem()
{
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
  QRectF rect = boundingRect();
  QBrush background(Qt::blue);

  if (m_mouse_pressed) {
    background.setColor(Qt::red);
  }
  else {
    background.setColor(Qt::green);
  }

  painter->fillRect(rect, background);
  painter->drawRect(rect);

  //painter->setBrush(Qt::yellow);
  //painter->drawRoundedRect(0, 0, 30, 30, 5, 5);

  //drawPie(0,0,30,30,-45*16,-270*16);
}

QRectF GraphicsItem::boundingRect() const
{
  return QRectF(0, 0, 50, 50);
}

void GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
  QGraphicsItem::contextMenuEvent(event);

  QMenu menu;
  QAction *xAction = menu.addAction("XXX");
  QAction *yAction = menu.addAction("YYY");

  QAction *selected = menu.exec(event->screenPos());
}

void GraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  QGraphicsItem::dragEnterEvent(event);

  qDebug() << "dragEnterEvent" << event->mimeData()->formats().join(" ");
  event->setAccepted(event->mimeData()->hasFormat("text/plain"));
}

void GraphicsItem::focusInEvent(QFocusEvent *event)
{
  QGraphicsItem::focusInEvent(event);

}

void GraphicsItem::focusOutEvent(QFocusEvent *event)
{
  QGraphicsItem::focusOutEvent(event);

}

void GraphicsItem::keyPressEvent(QKeyEvent *event)
{
  QGraphicsItem::keyPressEvent(event);

  switch(event->key()) {
    case Qt::Key_Left:
      moveBy(-10, 0);
      break;
    case Qt::Key_Right:
      moveBy(10, 0);
      break;
    case Qt::Key_Up:
      moveBy(0, -10);
      break;
    case Qt::Key_Down:
      moveBy(0, 10);
      break;
  }

  update();
}

void GraphicsItem::keyReleaseEvent(QKeyEvent *event)
{
  QGraphicsItem::keyReleaseEvent(event);
}

void GraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}

void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  m_mouse_pressed = true;

  update();

  QGraphicsItem::mousePressEvent(event);
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  m_mouse_pressed = false;

  update();

  QGraphicsItem::mouseReleaseEvent(event);
}

