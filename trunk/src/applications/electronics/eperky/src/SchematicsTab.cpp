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

#include <QApplication>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "SchematicsScene.h"
#include "SchematicsTab.h"

SchematicsTab::SchematicsTab(QWidget *parent /*=0*/)
 : QFrame(parent)
{
  //setFrameStyle(Sunken | StyledPanel);

  m_view = new QGraphicsView(this);
  m_view->setRenderHint(QPainter::Antialiasing, false);
  //m_view->setRenderHint(QPainter::Antialiasing);
  //m_view->setCacheMode(QGraphicsView::CacheBackground);
  //Index
  //m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  m_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  m_view->setDragMode(QGraphicsView::ScrollHandDrag);
  //m_view->setDragMode(QGraphicsView::RubberBandDrag);
  m_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);

  //m_view->setBackgroundBrush(Qt::white); // instead of scene background

  // If you have a QTabBar with a QFrame as tab containing a layout with a QGraphicsView
  // you need this to remove an appearing margin (about 4px) inside of QFrame. This also
  // removes the 1px black border of the QFrame. The same result has:
  // m_view->setStyleSheet( "QGraphicsView { border-style: none; }" );
  m_view->setFrameShape(QFrame::NoFrame);

  m_scene = new SchematicsScene(m_view);
  m_scene->setSceneRect(0, 0, 400, 400);
  m_view->setScene(m_scene);

  QGraphicsRectItem *r = new QGraphicsRectItem(80, 80, 100, 100);
  m_scene->addItem(r);
  m_scene->addText("Test");

  m_view->show();



/*
  QPalette pal = palette();
  pal.setColor(backgroundRole(), QColor("red"));
  setPalette(pal);
  setBackgroundRole(QPalette::Background);
  setAutoFillBackground(true);
*/

  QHBoxLayout *layout = new QHBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);        // Else there would be a 5px margin around the graphics view.
  layout->addWidget(m_view);
  setLayout(layout);
}

SchematicsTab::~SchematicsTab()
{
  if (m_scene) {
    delete m_scene; m_scene = 0;
  }

  if (m_view) {
    delete m_view; m_view = 0;
  }
}

