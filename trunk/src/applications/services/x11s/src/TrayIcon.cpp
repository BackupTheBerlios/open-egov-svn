// $Id$
//
// Open eGovernment
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

#include <OEG/Qt/Application.h>

#include <QAction>
#include <QApplication>
#include <QByteArray>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QHostAddress>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVBoxLayout>

#include "Connection.h"
#include "X11defines.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon(QWidget *parent /*=0*/)
 : QSystemTrayIcon(parent)
{
  createActions();

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

  m_tray_icon = new QIcon;
  //m_tray_icon->addFile(":/application.ico");
  //setWindowIcon(*m_tray_icon);
  connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
  setIcon(*m_tray_icon);

  m_ip_address      = "";
  m_server_number   = 0;
  m_auto_exit_x11s  = true;
  m_auto_exit_time  = 3600;  // 1 hour.
  m_hide_everything = false;
  m_disable_bell    = true;

  QHostAddress host_adress;
  if (m_ip_address.isEmpty()) {
    host_adress  = QHostAddress(QHostAddress::LocalHost);
    m_ip_address = "local"; // host_adress.toString();
  }
  else if (m_ip_address == "any") {
    host_adress  = QHostAddress(QHostAddress::Any);
  }
  else if (m_ip_address == "local") {
    host_adress  = QHostAddress(QHostAddress::LocalHost);
  }
  else {
    host_adress.setAddress(m_ip_address);
  }

  m_server = new QTcpServer(this);
  if (! m_server->listen(host_adress, 6000 + m_server_number)) {
    QMessageBox::critical(0, qApp->applicationName(),
                          QString(_("Unable to start the server: %1.")).arg(m_server->errorString()));
    QCoreApplication::quit();
    return;
  }

  qDebug() << "Host:" << m_server->serverAddress().toString() << "Port:" << m_server->serverPort();

  showMessage(qApp->applicationName(),
              QString(_("The server is running on\n\nIP: %1\nPort: %2\n\n"))
                     .arg(m_server->serverAddress().toString()).arg(m_server->serverPort()));

  connect(m_server, SIGNAL(newConnection()),
          this,     SLOT(onNewConnection()));

}

TrayIcon::~TrayIcon()
{
  while (! m_connections.isEmpty()) {
    Connection *connection = m_connections.takeFirst();
    if (connection) {
      delete connection;
    }
  }

  if (m_server) {
    m_server->close();
    delete m_server; m_server = 0;
  }

  if (m_tray_icon) {
    delete m_tray_icon; m_tray_icon = 0;
  }
}

void TrayIcon::createActions()
{
  m_action_exit = new QAction(_("E&xit"), this);
  m_action_exit->setShortcut(QKeySequence(_("Ctrl+Q")));
  m_action_exit->setStatusTip(_("Exit the application"));
  connect(m_action_exit, SIGNAL(triggered()), this, SLOT(action_exit()));

  m_action_info = new QAction(_("&Information ..."), this);
  m_action_info->setShortcut(QKeySequence(_("Ctrl+I")));
  m_action_info->setStatusTip(_("Open a information dialog with statistical data"));
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

void TrayIcon::action_about_app()
{
  OEG::Qt::Application::runComponent("about-dialog");
}

void TrayIcon::action_help()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "index");
}

void TrayIcon::action_information()
{
  QString s = QString(_("Number of connections: %1")).arg(m_connections.count());

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

void TrayIcon::onNewConnection()
{
  qDebug() << "onNewConnection(): New connection.";
  Connection *conn = new Connection(m_server->nextPendingConnection());
  if (conn)
    m_connections.append(conn);
}

