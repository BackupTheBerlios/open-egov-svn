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

#include <QObject>

#include <QtCore>
#include <QtGui>

#include "View.h"

class ViewEditor : public View
{
  Q_OBJECT

  public:
    ViewEditor(QWidget *parent = 0);

    virtual void doEditZoomIn();
    virtual void doEditZoomNormal();
    virtual void doEditZoomOut();

    void openFileQuiet(const QString &fileName);    // Called from MainWindow after the tab was created.

  protected:
    void setStandardFont();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

  public slots:
    void newDocument();
    void open();
    bool save();
    bool saveAs();

  protected:
    QTextEdit      *m_editor;
    QTextDocument  *m_document;
    QTextCursor    *m_cursor;
    QFont          *m_font;
    QString         m_filename;
};

