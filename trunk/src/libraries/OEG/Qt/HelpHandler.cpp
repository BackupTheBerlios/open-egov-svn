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

#include <QtCore>
#include <QtGui>

#include <QApplication>

#include <OEG/Qt/Application.h>
#include <OEG/Qt/HelpHandler.h>
//#include <OEG/Qt/HelpWindow.h>
#include <OEG/Qt/MessageDialog.h>
#include <OEG/Qt/Settings.h>

using namespace OEG::Qt;

HelpHandler::HelpHandler(QWidget *parent)
 : QObject(parent)
{
  //m_help_window = 0;
}

HelpHandler::~HelpHandler()
{
  //if (m_help_window)
  //  m_help_window->close();
}

void HelpHandler::openHelp()
{
  //if (! m_help_window) {
  //  m_help_window = new HelpWindow();

  //  connect(m_help_window, SIGNAL(helpWindowClosed()),
  //          this,          SLOT(helpWindowClosed()));
  //}

  //m_help_window->show();
}

void HelpHandler::showHelp(const QUrl &url)
{
  //GASI::Qt::MessageBox::InfoMessage(url.toString());

  openHelp();

  OEG::Qt::Application::runComponent("help-viewer", QStringList() << dynamic_cast<OEG::Qt::Application *>(qApp)->baseName());

  //m_help_window->showHelp(url);
}

void HelpHandler::helpWindowClosed()
{
  //m_help_window = 0;
}

