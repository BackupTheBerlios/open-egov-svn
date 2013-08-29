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

#include <OEG/Common.h>
#include <OEG/Qt/Application.h>
#include <OEG/Qt/Connector.h>
#include <OEG/Qt/HelpHandler.h>
#include <OEG/Qt/DBusStandardInterface.h>
#include <OEG/Qt/DebugMessageHandler.h>

#include <QDesktopServices>
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

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace OEG::Qt;
using namespace Qt;

Application::Application(int &argc, char *argv[], const QString &base)
 : QApplication(argc, argv), m_database_manager(0), m_tray_icon(0), m_connector(0)
{
  srand(time(0));

  qInstallMessageHandler(OEG_DebugMessageHandler);

  setBaseName(base);                                       // Set it before any use of gettext or settings!
  installGetText();                                        // Init gettext.

  setOrganizationName(_("G.A.S.I."));
  setOrganizationDomain(_("open-egov.de"));

  QSettings settings(organizationName(), baseName());
  if (settings.status() != QSettings::NoError) {
    qDebug() << __FILE__ ": settings error: " << settings.status();
  }

  if (1) { // TODO: ask settings
    m_database_manager = new OEG::Qt::DatabaseManager();
  }

  QDir::setCurrent(standardDirectory(Base));               // Change into a well-known directory.

  QDesktopServices::setUrlHandler("help", &m_help_handler, "showHelp");

  // Initialize D-Bus. The Interface is a proxy to provide selected slots for D-Bus.
  // Maybe it is possible to export all scriptable slots of a object without proxy,
  // but so it is ensured that only the slots which should be public are accessible.

#if 0
need to find a recent windbus first
  if (! QDBusConnection::sessionBus().isConnected()) {
    qWarning("Cannot connect to the D-Bus session bus.\n"
             "Please check your system settings and try again.\n"
             "To start it, run: 'dbus-launch --auto-syntax'\n"
             "D-Bus support is disabled for this application.\n");
  }

  QDBusConnection::sessionBus().registerService("de.gasi.open-egov." + baseName());
  new DBusStandardInterface(this);
#endif

  m_connector = new OEG::Qt::Connector(this);

  m_connector->connectToServer();

  m_application_flags = AF_None;
}

Application::~Application()
{
  if (m_connector) {
    m_connector->disconnectFromServer();

    delete m_connector; m_connector = 0;
  }

  if (m_database_manager) {
    delete m_database_manager; m_database_manager = 0;
  }

  removeSystemTrayIcon();
}

void Application::installGetText()
{
  //setlocale(LC_ALL, "de_DE");
  setlocale(LC_ALL, QLocale::system().name().toLatin1().constData());

  QByteArray a = baseName().toLatin1();
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

// Allows setting an icon derived from QSystemTrayIcon,
// which should be handled/removed by the application.

void Application::setSystemTrayIcon(QSystemTrayIcon *icon)
{
  removeSystemTrayIcon();

  m_tray_icon = icon;

  m_tray_icon->show();
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
  QString path;
  QDir dir;

  switch (type) {
    case Temp:
      return QDir::toNativeSeparators(QDir::tempPath());

    case Home:    // C:/Documents and Settings/Username
      return QDir::toNativeSeparators(QDir::homePath());

    case Common:  // C:\Programme\Gemeinsame Dateien\open-egovernment\resources
      path = standardDirectory(Base) + "/share/open-egovernment";
      return QDir::toNativeSeparators(QDir::cleanPath(path));
      break;

    case Data:
      dir.cd(standardDirectory(Base));

      if (dir.exists("data/" + baseName()))
        dir.cd("data/" + baseName());

      return dir.canonicalPath();
      break;

    case Base:
      path = QCoreApplication::applicationDirPath();
	  if (path.endsWith("/bin"))
	    path = path.left(path.length() - 4);
      return QDir::cleanPath(path);
      break;

    case User:
      path = standardDirectory(Base) + "/users/";
#ifdef _WIN32
      {
        TCHAR userNameBuffer[100];
        DWORD userNameLength = sizeof(userNameBuffer);
        if (GetUserName(userNameBuffer, &userNameLength)) {          // Win32 API.
          path += QString::fromWCharArray(userNameBuffer);
        }
      }
#else
      path += getlogin();                                            // Linux.
#endif
      if (dir.exists(path)) {
        return QDir::cleanPath(path);
      }
      break;
  }

  return QString();
}

QString Application::locateFile(const QString &filename, FileType type /*=Unknown*/)
{
  QString path;
  QDir    dir;

  switch (type) {
    case Icon:
      {
        // TODO: avoid change dirs, simplify, icon management!

        dir.cd(standardDirectory(Home));
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

        dir.cd(standardDirectory(Base));
        if (dir.exists("resources/icons")) {
          dir.cd("resources/icons");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        dir.cd(standardDirectory(Base));
        if (dir.exists("share/icons/default profile/standard")) {
          dir.cd("share/icons/default profile/standard");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
          if (QFile::exists(dir.canonicalPath() + "/" + filename + ".svg"))
            return dir.canonicalPath() + "/" + filename + ".svg";
          if (QFile::exists(dir.canonicalPath() + "/" + filename + ".png"))
            return dir.canonicalPath() + "/" + filename + ".png";
        }

        qWarning() << "Icon not found! Checked in home/common/base resources dir.";

        return QString();
      }
      break;

    case UserDatabase:
      {
        path = standardDirectory(User) + "/db/" + filename;

		if (QFile::exists(path))
          return QDir::cleanPath(path);

        qWarning() << "Database not found! Checked in users/username/db directory.";

        return QString();
      }
      break;

    case Database:
      {
        path = standardDirectory(Base) + "/db/" + filename;

		if (QFile::exists(path))
          return QDir::cleanPath(path);

        qWarning() << "Database not found! Checked in db directory.";

        return QString();
      }
      break;

    case Image:
      break;

    case Text:
      break;

    case Help:
      {
        QString lang = QLocale::system().name();

        // Help files are always there, were also the program files are located.

        dir.cd(standardDirectory(Base));
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
        dir.cd(standardDirectory(Base));
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

        dir.cd(standardDirectory(Home));
        if (dir.exists("plugins")) {
          dir.cd("plugins");
          if (QFile::exists(dir.canonicalPath() + "/" + filename))
            return dir.canonicalPath() + "/" + filename;
        }

        qWarning() << "Plugin not found! Checked in app/common/home plugins dir.";

        return QString();
      }
      break;

    case Unknown:
      break;
  }

  return path;
}

// Removal of flags is not needed, because they are used to mark an application's
// requirements and such things are constant values.

void Application::addApplicationFlags(ApplicationFlags set)
{
  m_application_flags &= set;
}

