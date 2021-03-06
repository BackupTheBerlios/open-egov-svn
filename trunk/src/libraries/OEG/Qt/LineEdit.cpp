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

#include <OEG/Qt/LineEdit.h>

#include <QToolButton>
#include <QIcon>
#include <QStyle>
#include <QStyleOption>
#include <QColor>
#include <QPainter>

using namespace OEG::Qt;
using namespace Qt;

LineEdit::LineEdit(QWidget *parent /*=0*/)
 : QLineEdit("", parent)
{
}

LineEdit::LineEdit(const QString &contents, QWidget *parent /*=0*/)
 : QLineEdit(contents, parent), m_clear_button(0)
{
  addClearButton();
}

LineEdit::~LineEdit()
{
  if (m_clear_button) {
    delete m_clear_button; m_clear_button = 0;
  }
}

void LineEdit::addClearButton()
{
  m_clear_button = new QToolButton(this);

  if (! m_clear_button)
    return;

  m_clear_button->setCursor(ArrowCursor);
  m_clear_button->setStyleSheet("QToolButton { border: none; padding: 0px; }");
  m_clear_button->setToolTip(_("Clear the text."));
  m_clear_button->hide();

  connect(m_clear_button, SIGNAL(clicked()),
          this,           SLOT(clear()));
  connect(this,           SIGNAL(textChanged(const QString &)),
          this,           SLOT(onTextChanged(const QString &)));
}

void LineEdit::resizeEvent(QResizeEvent *event)
{
}

void LineEdit::onTextChanged(const QString &text)
{
  if (! m_clear_button)
    return;

  m_clear_button->setVisible(! text.isEmpty());
}

