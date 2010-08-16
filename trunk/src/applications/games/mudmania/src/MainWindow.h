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

#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/TabWidget.h>

#include <QScriptEngine>
#include <QString>
#include <QList>
#include <QWidget>

class Splitter;
class QScriptEngine;
class MultiLineEdit;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  //Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void createActions();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createDockWidgets();

    void createJavaScriptObjects();
    void runJavaScript(const QString &s);
    void runJavaScriptFromFile(const QString &fileName);

  protected:
    OEG::Qt::TabWidget *m_tabs;
    MultiLineEdit      *m_input;
    QString             m_title;
    Splitter           *m_splitter;
    QScriptEngine       m_engine;
};

