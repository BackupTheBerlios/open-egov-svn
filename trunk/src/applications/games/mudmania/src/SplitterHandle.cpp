// $Id$

#include <OEG/Common.h>

#include <QApplication>
#include <QLatin1String>

#include <QGradient>
#include <QPainter>
#include <QPaintEvent>

#include "SplitterHandle.h"

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *parent)
 : QSplitterHandle(orientation, parent)
{
}

void SplitterHandle::paintEvent(QPaintEvent *event)
{
  QSplitterHandle::paintEvent(event);
return;

  QPainter painter(this);
  if (orientation() == Qt::Horizontal) {
         //gradient.setStart(rect().left(), rect().height()/2);
         //gradient.setFinalStop(rect().right(), rect().height()/2);
  } else {
         //gradient.setStart(rect().width()/2, rect().top());
         //gradient.setFinalStop(rect().width()/2, rect().bottom());
  }

  //painter.fillRect(event->rect(), QBrush(gradient));
}

