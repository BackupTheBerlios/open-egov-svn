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

#pragma once

#include <QString>
#include <QList>
#include <QTextEdit>

#include "HistoryEntry.h"

class QWidget;
class QKeyEvent;

class MultiLineEdit : public QTextEdit
{
  Q_OBJECT

  public:
    MultiLineEdit(QWidget *parent = 0);
    virtual ~MultiLineEdit();

  protected:
    void setStandardFont();

  protected:
    virtual void keyPressEvent(QKeyEvent *event);

  public slots:
    void addToHistory(const QString &text);

  signals:
    void sendText(const QString &text);

  protected:
    bool                   m_auto_clear;
    QList<HistoryEntry *>  m_history;
    int                    m_history_pos;
};

