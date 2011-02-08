// $Id: MainWindow.cpp 356 2010-12-21 09:47:43Z gerrit-albrecht $
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

#include <QApplication>

#include <QHBoxLayout>
#include <QGraphicsView>

#include "SchematicsView.h"

SchematicsView::SchematicsView(QWidget *parent /*=0*/)
 : QFrame(parent)
{
  //setFrameStyle(Sunken | StyledPanel);

  m_graphics_view = new QGraphicsView(this);
  m_graphics_view->setRenderHint(QPainter::Antialiasing, false);
  m_graphics_view->setDragMode(QGraphicsView::RubberBandDrag);
  m_graphics_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  m_graphics_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  //m_graphics_view->setBackgroundBrush(new QBrush(new QColor(QColor::white)));
  //m_graphics_view->setCacheMode(new QGraphicsView::CacheMode(QGraphicsView::CacheModeFlag::CacheBackground));

  // If you have a QTabBar with a QFrame as tab containing a layout with a QGraphicsView
  // you need this to remove an appearing margin (about 4px) inside of QFrame. This also
  // removes the 1px black border of the QFrame. The same result has:
  // m_graphics_view->setStyleSheet( "QGraphicsView { border-style: none; }" );
  m_graphics_view->setFrameShape(QFrame::NoFrame);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(m_graphics_view);
  setLayout(layout);
}

SchematicsView::~SchematicsView()
{
  if (m_graphics_view) {
    delete m_graphics_view; m_graphics_view = 0;
  }
}

