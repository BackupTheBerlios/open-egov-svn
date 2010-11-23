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

#include <QDir>
#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QDebug>

#include <stdlib.h>
#include <time.h>

using namespace OEG::Qt;
using namespace Qt;

Application::Application(int &argc, char *argv[], const QString &base)
 : QApplication(argc, argv), m_tray_icon(0)
{
  srand(time(0));

  setBaseName(baseName);                                   // Set it before any use of gettext or settings!
  installGetText();                                        // Init gettext.

  setOrganizationName(_("G.A.S.I."));
  setOrganizationDomain(_("open-egov.de"));

  QSettings settings(organizationName(), baseName());
  if (settings.status() != QSettings::NoError) {
    qDebug() << __FILE__ ": settings error: " << settings.status();
  }
}

Application::~Application()
{
  removeSystemTrayIcon();
}

void Application::installGetText()
{
  //setlocale(LC_ALL, "de_DE");
  setlocale(LC_ALL, QLocale::system().name().toLatin1().constData());

  QByteArray a = baseName().toAscii();
  bindtextdomain(a.constData(), "locale");
  textdomain(a.constData());
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

void Application::setApplicationName(const QString &name, const QString &version /*=""*/)
{
  QCoreApplication::setApplicationName(name);

  setApplicationVersion(version);
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

void Application::setBaseName(const QString &baseName)
{
  m_basename = baseName;

  if (baseName.isEmpty()) {
    QString appName = applicationName();

    if (appName.length() > 0) {
      setBaseName(appName.toLower());                                // Caution: appName wants to be a localized string!
    }
  }

  if (homepage().isEmpty()) {                                        // Generate a homepage URL.
    setHomepage("http://www.open-egov.de/applications/" + baseName + "/");
  }
}

QString Application::baseName() const
{
  return m_basename;
}

void Application::setHomepage(const QString &url)
{
  m_homepage = url;
}

QString Application::homepage() const
{
  return m_homepage;
}

void Application::addSystemTrayIcon(const QIcon &icon, QMenu *menu, const QString &title)
{
  if (! QSystemTrayIcon::isSystemTrayAvailable()) {
    QMessageBox::critical(0, _("Systray"), _("Couldn't detect system tray."));
    return;
  }

  removeSystemTrayIcon();

  m_tray_icon = new QSystemTrayIcon(this);
  m_tray_icon->setIcon(icon);
  m_tray_icon->setToolTip(title);
  if (menu)
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

QString Application::standardDirectory(DirectoryType type)
{
  switch (type) {
    case Temp:
      return QDir::tempPath();

    case User:
      return QDir::homePath();

    case Common:  // C:\Programme\Gemeinsame Dateien\GASI\resources
      return standardDirectory(Temp); // TODO
      break;

    case Program:
      {
        QDir dir(QCoreApplication::applicationDirPath());

        if (dir.dirName() == "bin")
          dir.cdUp();

        return dir.canonicalPath();
      }
      break;
  }

  return QString();
}

QString Application::locateFile(const QString &filename, FileType type /*=Unknown*/)
{
  QString path;

  switch (type) {
    case Icon:
      {
        QDir dir;

        // TODO: avoid change dirs

        dir.cd(standardDirectory(User));
        if (dir.exists("resources/icons")) {
          dir.cd("resources/icons");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        dir.cd(standardDirectory(Common));
        if (dir.exists("resources/icons")) {
          dir.cd("resources/icons");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        dir.cd(standardDirectory(Program));
        if (dir.exists("resources/icons")) {
          dir.cd("resources/icons");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        qWarning() << "Icon not found! Checked in user/common/app resources dir.";

        return QString();
      }
      break;

    case Database:
      {
        QDir dir;

        // A database is always in the program folder. TODO: allows other directories.

        dir.cd(standardDirectory(Program));
        //if (dir.exists("db")) {
        //  dir.cd("db");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        //}

        qWarning() << "Database not found! Checked only in program dir/db.";

        return QString();
      }
      break;

    case Image:
      break;

    case Text:
      break;

    case Help:
      {
        QDir dir;
        QString lang = QLocale::system().name();

        // Help files are always there, were also the program files are located.

        dir.cd(standardDirectory(Program));
        if (dir.exists("help")) {
          dir.cd("help");
          if (dir.exists(lang))
            dir.cd(lang);
          else if (dir.exists("en_US"))
            dir.cd("en_US");
          //GASI::Qt::MessageBox::InfoMessage(dir.canonicalPath());
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        qWarning() << "Help text not found! Checked in app/help dir.";

        return QString();
      }
      break;

    case Plugin:
      {
        QDir dir;

        dir.cd(standardDirectory(Program));
        if (dir.exists("plugins")) {
          dir.cd("plugins");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        dir.cd(standardDirectory(Common));
        if (dir.exists("plugins")) {
          dir.cd("plugins");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        dir.cd(standardDirectory(User));
        if (dir.exists("plugins")) {
          dir.cd("plugins");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        qWarning() << "Plugin not found! Checked in app/common/user plugins dir.";

        return QString();
      }
      break;

    case Unknown:
      break;
  }

  return path;
}

