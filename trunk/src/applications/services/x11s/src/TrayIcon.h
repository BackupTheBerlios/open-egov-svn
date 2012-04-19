// $Id$
//
// Open eGovernment
// Copyright (C) 2004-2012 by Gerrit M. Albrecht
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
class Server;

class TrayIcon : public QSystemTrayIcon
{
  Q_OBJECT

  public:
    TrayIcon(QWidget *parent = 0);
    virtual ~TrayIcon();

    void setServer(Server *server);

  protected:
    void createActions();

  public slots:
    void updateTrayIcon();

  private slots:
    void action_about_app();
    void action_help();
    void action_exit();
    void action_information();

    void onActivated(QSystemTrayIcon::ActivationReason reason);

  protected:
    Server              *m_server;                         // Server object.
    QMenu               *m_tray_icon_menu;                 // Context menu when clicked at the icon.
    QIcon               *m_tray_icon;                      // Currently displayed tray icon.
    bool                 m_hide_everything;                // Don't show the user interface.

    QAction             *m_action_exit;
    QAction             *m_action_info;
    QAction             *m_action_help;
    QAction             *m_action_about_app;
    QAction             *m_action_about_qt;
};

