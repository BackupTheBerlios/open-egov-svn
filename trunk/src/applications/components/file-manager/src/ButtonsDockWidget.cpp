// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>

#include <QDebug>

#include "ButtonsDockWidget.h"

ButtonsDockWidget::ButtonsDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
 : QDockWidget(title, parent, flags)
{
  construct();
}

ButtonsDockWidget::ButtonsDockWidget(QWidget *parent /*=0*/, Qt::WindowFlags flags)
 : QDockWidget(parent, flags)
{
  construct();
}

void ButtonsDockWidget::construct()
{
  setFeatures(QDockWidget::DockWidgetVerticalTitleBar |    // QDockWidget::NoDockWidgetFeatures
              QDockWidget::DockWidgetClosable         |
              QDockWidget::DockWidgetMovable          |
              QDockWidget::DockWidgetFloatable);

  createPushButton("compare",          _("Compare"));
  createPushButton("copy",             _("Copy"));
  createPushButton("move",             _("Move"));
  createPushButton("parent",           _("Parent"));
  createPushButton("delete",           _("Delete"));
  createPushButton("run",              _("Run"));
  createPushButton("rename",           _("Rename"));
  createPushButton("open",             _("Open"));
  createPushButton("new-directory",    _("New Dir"));
  createPushButton("console",          _("Console"));
  createPushButton("select-all",       _("Sel. All"));
  createPushButton("select-none",      _("Sel. Non"));
  createPushButton("invert-selection", _("Sel. Inv"));
  createPushButton("script 1",         _("Script 1"));

  QWidget *w = new QWidget(this);
  QGridLayout *layout = new QGridLayout(0);
  layout->addWidget(m_buttons.at( 0), 0, 0);
  layout->addWidget(m_buttons.at( 1), 0, 1);
  layout->addWidget(m_buttons.at( 2), 0, 2);
  layout->addWidget(m_buttons.at( 3), 0, 3);
  layout->addWidget(m_buttons.at( 4), 0, 4);
  layout->addWidget(m_buttons.at( 5), 0, 5);
  layout->addWidget(m_buttons.at( 6), 1, 0);
  layout->addWidget(m_buttons.at( 7), 1, 1);
  layout->addWidget(m_buttons.at( 8), 1, 2);
  layout->addWidget(m_buttons.at( 9), 1, 3);
  layout->addWidget(m_buttons.at(10), 1, 4);
  layout->addWidget(m_buttons.at(11), 1, 5);
  layout->addWidget(m_buttons.at(12), 2, 0);
  layout->addWidget(m_buttons.at(13), 2, 1);
  w->setLayout(layout);
  setWidget(w);
}

ButtonsDockWidget::~ButtonsDockWidget()
{
}

void ButtonsDockWidget::paintEvent(QPaintEvent *event)
{
  QDockWidget::paintEvent(event);
}

// Called after clicking a button from the dock. The parameter is
// the internal command name (e.g. "copy") for the button's command.

void ButtonsDockWidget::buttonClicked(const QString &name)
{
  qDebug() << "BTN CLICKED: " << name;
}

QPushButton *ButtonsDockWidget::createPushButton(const QString &name, const QString &title)
{
  QPushButton *button;

  button = new QPushButton(title, this);
  button->setObjectName("pushbutton_" + name);

  m_buttons << button;

  QSignalMapper *signal_mapper = new QSignalMapper(this);            // We want to know which button was pressed without subclassing
  connect(button,        SIGNAL(clicked()),                          // QPushButton and reacting to clicked() by signalling clicked(this).
          signal_mapper, SLOT(map()));                               // The QSignalMapper maps from one object to another object and
  signal_mapper->setMapping(button, name);                           // gives back the result with its mapped() signal.
  connect(signal_mapper, SIGNAL(mapped(const QString &)),            // Simple and elegant. A reason why I like programming with Qt :-)
          this,          SLOT(buttonClicked(const QString &)));
  connect(signal_mapper, SIGNAL(mapped(const QString &)),            // Receiver is the MainWindow in this case.
          this,          SIGNAL(sendCommand(const QString &)));

  return button;
}

QPushButton *ButtonsDockWidget::findPushButton(const QString &name)
{
  QPushButton *button;

  for (int i=0; i<m_buttons.size(); i++) {
    button = m_buttons.at(i);
    if (button->objectName() == name)
      return button;
  }
  
  return 0;
}

