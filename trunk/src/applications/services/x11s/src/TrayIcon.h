// $Id$
//
// Open-eGovernment
// Copyright (C) 2004-2010 by Gerrit M. Albrecht
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

#include <QSystemTrayIcon>
#include <QString>

class QAction;
class QIcon;
class QMenu;
class QTcpServer;
class QTcpSocket;

class TrayIcon : public QSystemTrayIcon
{
  Q_OBJECT

  public:
    TrayIcon(QWidget *parent = 0);
    ~TrayIcon();

    void createActions();

  private slots:
    void action_about_app();
    void action_help();
    void action_exit();

    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void onNewConnection();

  protected:
    QTcpServer   *m_server;
    QTcpSocket   *m_connection;
    QMenu        *m_tray_icon_menu;
    QIcon        *m_tray_icon;
    QAction      *m_action_exit;
    QAction      *m_action_help;
    QAction      *m_action_about_app;
    QAction      *m_action_about_qt;

    QString       m_ip_address;         // The IP address the server uses.
    unsigned int  m_server_number;      // 0 .. x, maps to port number 6000 .. 6000+x.
    bool          m_auto_exit_x11s;     // If the last window closes X11S exists.
    unsigned int  m_auto_exit_time;     // After closing last window the server waits X seconds.
    bool          m_hide_everything;    // For DAU work places.
    bool          m_disable_bell;       // Be nice.
};
