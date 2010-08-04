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

#include <OEG/Common.h>

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QDebug>

class QToolButton;
class QResizeEvent;

namespace OEG { namespace Qt {

// This line edit widget provides a clear text button.

class LineEdit : public QLineEdit
{
  Q_OBJECT

  public:
    LineEdit(QWidget *parent = 0);
	LineEdit(const QString &contents, QWidget *parent = 0);
    ~LineEdit();

  protected:
    void resizeEvent(QResizeEvent *event);

  private slots:
    void onTextChanged(const QString &text);

  private:
    QToolButton *m_clear_button;
};

}}

