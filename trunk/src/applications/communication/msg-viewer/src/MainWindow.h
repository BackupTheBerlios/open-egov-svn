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

#pragma once

#include <OEG/Qt/MainWindow.h>
#include <OEG/Mail/Mail.h>

#include <QFile>
#include <QByteArray>
#include <QList>
#include <QString>

class QAction;
class QMenu;
class QTextEdit;
class QAuthenticator;

class DirectoryEntry;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void skipBytes(int bytes);
    long long int readNumber(int bytes);
    long long int vbNumber(const QByteArray &s);
    QByteArray sectorReader(int sect_size, int sid);
    void parseMessageFile(const QString &fileName);

  private slots:
    virtual void createActions();
    virtual void createStatusBar();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createTabbedMenuBar();

    void standardActionOpen();

  private:
    OEG::Mail::Mail          m_mail;                       // An E-Mail object filled by the plugin which parsed the file.
    QString                  m_file_name;                  // Filename of the mail returned by the file selection dialog.
    QTextEdit               *m_text;                       // Displays the E-Mail nicely.
    QFile                    m_file;                       // File object which belongs to the filename.
    QList<DirectoryEntry *>  m_dirs;                       // A list with directories provided by the MSG file.
    QString                  m_current_list;               // 
    QMenu                   *m_menu_file;                  // GUI element.
    QToolBar                *m_toolbar_file;               // GUI element.
    QAction                 *m_action_get_new_list;        // TODO.
    QAction                 *m_action_get_file;            // TODO.
};

