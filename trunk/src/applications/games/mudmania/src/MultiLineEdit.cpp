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

#include <QFont>
#include <QKeyEvent>
#include <QVariant>

#include "MultiLineEdit.h"

MultiLineEdit::MultiLineEdit(QWidget *parent /*= 0*/)
 : QTextEdit(parent)
{
  m_auto_clear  = true;
  m_history_pos = 0;

  setStandardFont();
}

MultiLineEdit::~MultiLineEdit()
{
  while (! m_history.isEmpty())
    delete m_history.takeFirst();
}

void MultiLineEdit::setStandardFont()
{
  QFont font;

  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  setFont(font);
}

void MultiLineEdit::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Return) {
    QString str = toPlainText().append("\r\n");

    emit sendText(str);

    addToHistory(str);
    if (m_auto_clear)
      clear();

    return;
  }

  // Values: qt-x11-opensource-src-4.1.4444/src/gui/kernel/qkeysequence.cpp

  switch (event->key()) {
    case Qt::Key_Down:
      break;

    case Qt::Key_Up:
      break;

    default:
      QTextEdit::keyPressEvent(event);
  }
}

void MultiLineEdit::addToHistory(const QString &text)
{
  HistoryEntry *e = new HistoryEntry(text);

  if (! e)
    return;

  m_history.append(e);
}

