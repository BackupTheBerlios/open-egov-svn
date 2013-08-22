// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
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

#include "MainWindow.h"

#include <OEG/Qt/TabbedMenuBar.h>
#include <OEG/Mail/Mail.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_bug_report = "";
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createStatusBar()
{
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
  QMenu *menu;

  menu = getStandardMenu(FileMenu);
  menu->addAction(standardAction(Exit));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));

}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::sendBugReport()
{
  OEG::Mail::Mail mail;

  QString mailText = "";
  mailText += "simple test text\nsecond line\nand another....\n";
  mailText += "\n";
  mailText += "Application: " + m_base_name + "\n";
  mailText += "Date: " + QDateTime::currentDateTime().toString();

  mail.addHeaders(QStringList() << "To: automatic-bug-report@open-egov.de"
                                << "From: OEG User"
                                << "Subject: Bug-Report");
  mail.setText(mailText);
  mail.send();
}

