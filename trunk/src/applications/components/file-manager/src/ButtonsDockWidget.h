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

#pragma once

#include <QString>
#include <QList>
#include <QDockWidget>

class QPushButton;

class ButtonsDockWidget : public QDockWidget
{
  Q_OBJECT

  public:
    ButtonsDockWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ButtonsDockWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~ButtonsDockWidget();

    void construct();

  signals:
    void sendCommand(const QString &name);

  protected:
    void paintEvent(QPaintEvent *event);

    QPushButton *createPushButton(const QString &name, const QString &title);
    QPushButton *findPushButton(const QString &name);

  protected slots:
    void buttonClicked(const QString &name);

  private:
    QList<QPushButton *>  m_buttons;
};

