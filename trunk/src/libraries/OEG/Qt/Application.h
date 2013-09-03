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

#include <OEG/Common.h>
#include <OEG/Qt/DatabaseManager.h>
#include <OEG/Qt/HelpHandler.h>
#include <OEG/Qt/Settings.h>

#include <QApplication>
#include <QIcon>
#include <QString>
#include <QStringList>
#include <QDebug>

class QMenu;
class QSystemTrayIcon;

namespace OEG { namespace Qt {

class Connector;

class Application : public QApplication
{
  Q_OBJECT

  public:
    enum DirectoryType { Temp, Home, Common, Data, Base, User };
    enum FileType { Icon, Database, UserDatabase, Image, Text, Plugin, Help, Unknown };

    enum ApplicationFlag {                       // Flags are not frozen, they are in evaluation and may change...
      AF_Application = 0x00000001,               // This is an standard application.
      AF_Service     = 0x00000002,               // Application is a service.
      AF_Documents   = 0x00000004,               // Applciation may store documents and provides such functions.
      AF_Database    = 0x00000008,
      AF_Network     = 0x00000010,
      AF_PeerToPeer  = 0x00000020,
      AF_AdminRights = 0x00000040,               // Needs administrator rights to work. Automatic role change.
      AF_None        = 0x00000000                // Default value.
    };
    Q_DECLARE_FLAGS(ApplicationFlags, ApplicationFlag)

     // Guest, User, Admin; Roles, ...

  public:
    Application(int &argc, char *argv[], const QString &base);
    virtual ~Application();

    static void runComponent(const QString &cmd);
    static void runComponent(const QString &cmd, const QStringList &arguments);

    void setSystemTrayIcon(QSystemTrayIcon *icon);
    void addSystemTrayIcon(const QIcon &icon, QMenu *menu, const QString &title);
    void removeSystemTrayIcon();

    void setApplicationName(const QString &name, const QString &version = "");

    void setApplicationBuildData(const char *date, const char *time);
    QString applicationBuildDate() const;
    QString applicationBuildTime() const;

    void setHomepage(const QString &url);
    QString homepage() const;

    void setBaseName(const QString &baseName);
    QString baseName() const;

    QString standardDirectory(DirectoryType type);
    QString locateFile(const QString &filename, FileType type = Unknown);

    inline HelpHandler *helpHandler() { return &m_help_handler; }
    inline DatabaseManager *databaseManager() { return m_database_manager; }

    void addApplicationFlags(ApplicationFlags set);

  protected:
    void installGetText();

  protected:
    DatabaseManager   *m_database_manager;
    QSystemTrayIcon   *m_tray_icon;
    Connector         *m_connector;
    ApplicationFlags   m_application_flags;
    QString            m_application_build_date;
    QString            m_application_build_time;
    QString            m_homepage;
    QString            m_basename;
    Settings           m_settings;
    HelpHandler        m_help_handler;
};

}}

