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

#include <OEG/Qt/Application.h>

#include <QAction>
#include <QApplication>
#include <QByteArray>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>

#include "TrayIcon.h"
#include "Server.h"

TrayIcon::TrayIcon(QWidget *parent/*=0*/)
 : QSystemTrayIcon(parent), m_tray_icon(0)
{
  createActions();

  m_server = 0;

  m_tray_icon_menu = new QMenu;
  m_tray_icon_menu->addAction(m_action_help);
  m_tray_icon_menu->addSeparator();
  m_tray_icon_menu->addAction(m_action_info);
  m_tray_icon_menu->addSeparator();
  m_tray_icon_menu->addAction(m_action_about_app);
  m_tray_icon_menu->addAction(m_action_about_qt);
  m_tray_icon_menu->addSeparator();
  m_tray_icon_menu->addAction(m_action_exit);
  setContextMenu(m_tray_icon_menu);

  connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

  m_hide_everything = false;
}

TrayIcon::~TrayIcon()
{
  if (m_tray_icon) {
    //if (m_tray_icon->isVisible())
    //  m_tray_icon->hide();

    delete m_tray_icon; m_tray_icon = 0;
  }
}

void TrayIcon::setServer(Server *server)
{
  if (! server) {
    qDebug() << "TrayIcon::setServer(): server was 0.";
    return;
  }

  m_server = server;

  connect(m_server, SIGNAL(clientCountChanged()),
          this,     SLOT(updateTrayIcon()));
}

void TrayIcon::createActions()
{
  m_action_exit = new QAction(_("E&xit"), this);
  m_action_exit->setShortcut(QKeySequence(_("Ctrl+Q")));
  m_action_exit->setStatusTip(_("Exit the application"));
  connect(m_action_exit, SIGNAL(triggered()), this, SLOT(action_exit()));

  m_action_info = new QAction(_("&Information ..."), this);
  m_action_info->setShortcut(QKeySequence(_("Ctrl+I")));
  m_action_info->setStatusTip(_("Open a information dialog with informal/statistical data"));
  connect(m_action_info, SIGNAL(triggered()), this, SLOT(action_information()));

  m_action_help = new QAction(_("&Help"), this);
  m_action_help->setStatusTip(_("Open the help viewer"));
  connect(m_action_help, SIGNAL(triggered()), this, SLOT(action_help()));

  m_action_about_app = new QAction(_("About &App ..."), this);
  m_action_about_app->setStatusTip(_("Show the application's About box"));
  connect(m_action_about_app, SIGNAL(triggered()), this, SLOT(action_about_app()));

  m_action_about_qt = new QAction(_("About &Qt ..."), this);
  m_action_about_qt->setStatusTip(_("Show the Qt library's About box"));
  connect(m_action_about_qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

OEG::Qt::Application *TrayIcon::oegApp()
{
  return dynamic_cast<OEG::Qt::Application *>(qApp);
}

void TrayIcon::action_about_app()
{
  OEG::Qt::Application::runComponent("about-dialog", QStringList() << oegApp()->baseName());
}

void TrayIcon::action_help()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << oegApp()->baseName() << "index");
}

void TrayIcon::action_information()
{
  QString s = QString(_("Number of managed clients: %1")).arg(m_server->clientCount());

  QMessageBox::information(0, qApp->applicationName(), s, QMessageBox::Ok);
}

void TrayIcon::action_exit()
{
  hide();
  qApp->closeAllWindows();
  QCoreApplication::quit();
}

void TrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
  blockSignals(true);

  switch(reason) {
    case QSystemTrayIcon::Trigger:
      QMessageBox::information(0, qApp->applicationName(), _("Trigger"), QMessageBox::Ok);
      break;

    case QSystemTrayIcon::DoubleClick: 
      QMessageBox::information(0, qApp->applicationName(), _("DoubleClick"), QMessageBox::Ok);
      break;

    case QSystemTrayIcon::Context:
      break;

    case QSystemTrayIcon::MiddleClick:
      break;

    case QSystemTrayIcon::Unknown:
      break;
  }

  blockSignals(false);
}

void TrayIcon::updateTrayIcon()
{
  QString dir;

  if (m_tray_icon)
    delete m_tray_icon;

  dir = oegApp()->standardDirectory(OEG::Qt::Application::Data);

  if (m_server) {
    if (m_server->clientCount() > 0)
      m_tray_icon = new QIcon(dir + "/trayicon_in_use.ico");
    else
      m_tray_icon = new QIcon(dir + "/trayicon_ready.ico");
  }
  else {
    m_tray_icon = new QIcon(dir + "/trayicon_error.ico");
  }

  setIcon(*m_tray_icon);
}

