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

#include <QFile>
#include <QByteArray>
#include <QList>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTextEdit;
class QAuthenticator;
QT_END_NAMESPACE

class DirectoryEntry;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

    void skipBytes(int bytes);
    long long int readNumber(int bytes);
    long long int vbNumber(const QByteArray &s);
    QByteArray sectorReader(int sect_size, int sid);
    void parseMessageFile(const QString &fileName);

  private slots:
    //void getNewList();

  private:
    QTextEdit               *m_text;
    QFile                    m_file;
    QList<DirectoryEntry *>  m_dirs;
    QString                  m_current_list;
    QMenu                   *m_menu_file;
    QToolBar                *m_toolbar_file;
    QAction                 *m_action_get_new_list;
    QAction                 *m_action_get_file;
};

