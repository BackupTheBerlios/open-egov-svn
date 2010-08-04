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

#include <QtCore>
#include <QtGui>

#include "ConnectionThread.h"
#include "View.h"

class MultiLineEdit;

class ViewPlayer : public View
{
  Q_OBJECT

  public:
    ViewPlayer(QWidget *parent = 0);
    virtual ~ViewPlayer();

    void connect(const QString &host, unsigned int port, const QString &username, const QString &password);
    void disconnect();
    void reconnect();

    void insertText(const QString &text, unsigned int type = 0);
    void insertImage(const QString &path);

    void cursorDown();
    void scrollDown();

    QTextEdit *editor() const;

    void runFile(const QString &filename);
    void runScript(const QString &data);

  public slots:
    void receiveText(const QString &text);
    void receiveInput(const QString &text);
    void connectHost();

  signals:
    void sendText(const QString &text);

  protected:
    QTextEdit         m_editor;
    ConnectionThread *m_thread;

    QString           m_host;               // Used by connect() and connectHost().
    unsigned int      m_port;
    QString           m_username;
    QString           m_password;

    QTextCharFormat   m_fmt_output;         // Unclassified output.
    QTextCharFormat   m_fmt_input;          // Unclassified input.
    QTextCharFormat   m_fmt_comm_global;    // Public communication.
    QTextCharFormat   m_fmt_comm_private;   // Private communication.
    QTextCharFormat   m_fmt_comm_local;     // Local communication.
    QTextCharFormat   m_fmt_channel;   // Communication channel.
    QTextCharFormat   m_fmt_mail;      // Mail color.
    QTextCharFormat   m_fmt_news;      // News article.
    QTextCharFormat   m_fmt_room;      // .
    QTextCharFormat   m_fmt_item;      // .
    QTextCharFormat   m_fmt_npc;       // .
    QTextCharFormat   m_fmt_player;    // .
    QTextCharFormat   m_fmt_prompt;    // .
    QTextCharFormat   m_fmt_move;      // .
    QTextCharFormat   m_fmt_give;      // .
    QTextCharFormat   m_fmt_spam;      // .

    //QFont        m_fonts_spam;
    //QColor       m_colors_fg_spam;
    //QColor       m_colors_bg_spam;
};

