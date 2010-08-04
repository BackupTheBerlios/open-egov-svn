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

#include <OEG/Qt/Application.h>

#include <QMenu>
#include <QProcess>
#include <QSystemTrayIcon>

#include <stdlib.h>
#include <time.h>

using namespace OEG::Qt;
using namespace Qt;

Application::Application(int &argc, char *argv[])
 : QApplication(argc, argv), m_tray_icon(0)
{
  srand(time(0));

  m_basename = "";
}

Application::~Application()
{
  removeSystemTrayIcon();
}

void Application::runComponent(const QString &cmd)
{
  runComponent(cmd, QStringList());
}

void Application::runComponent(const QString &cmd, const QStringList &arguments)
{
  QProcess process;

  process.setWorkingDirectory(QCoreApplication::applicationDirPath());
  process.startDetached(cmd, arguments);
}

void Application::setApplicationVersion(const QString &version)
{
  m_application_version = version;
}

QString Application::applicationVersion() const
{
  return m_application_version;
}

void Application::setApplicationBuildData(const char *date, const char *time)
{
  m_application_build_date = date;
  m_application_build_time = time;
}

QString Application::applicationBuildDate() const
{
  return m_application_build_date;
}

QString Application::applicationBuildTime() const
{
  return m_application_build_time;
}

void Application::setHomepage(const QString &url)
{
  m_homepage = url;
}

void Application::setBaseName(const QString &basename)
{
  m_basename = basename;
}

QString Application::baseName() const
{
  if (m_basename.isEmpty())
    return applicationName().toLower();

  return m_basename;
}

QString Application::homepage() const
{
  return m_homepage;
}

void Application::addSystemTrayIcon(const QIcon &icon, QMenu *menu, const QString &title)
{
  removeSystemTrayIcon();

  m_tray_icon = new QSystemTrayIcon(this);
  m_tray_icon->setIcon(icon);
  m_tray_icon->setToolTip(title);
  m_tray_icon->setContextMenu(menu);
  m_tray_icon->show();
}

void Application::removeSystemTrayIcon()
{
  if (m_tray_icon) {
    if (m_tray_icon->isVisible())
      m_tray_icon->hide();

    delete m_tray_icon; m_tray_icon = 0;
  }
}

