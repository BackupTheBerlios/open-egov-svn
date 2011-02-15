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
#include <OEG/Qt/Settings.h>
#include <OEG/Qt/HelpHandler.h>

#include <QApplication>
#include <QIcon>
#include <QString>
#include <QStringList>
#include <QDebug>

class QMenu;
class QSystemTrayIcon;

namespace OEG { namespace Qt {

class Application : public QApplication
{
  Q_OBJECT

  public:
    enum DirectoryType { Temp, User, Common, Data, Base };
    enum FileType { Icon, Database, Image, Text, Plugin, Help, Unknown };

  public:
    Application(int &argc, char *argv[], const QString &base);
    virtual ~Application();

    static void runComponent(const QString &cmd);
    static void runComponent(const QString &cmd, const QStringList &arguments);

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

  protected:
    void installGetText();

  protected:
    QSystemTrayIcon *m_tray_icon;
    QString          m_application_build_date;
    QString          m_application_build_time;
    QString          m_homepage;
    QString          m_basename;
    Settings        *m_settings;
    HelpHandler      m_help_handler;
};

}}

