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

#include <QApplication>
#include <QWidget>

#include <OEG/Qt/MessageBox.h>

using namespace OEG::Qt;
using namespace Qt;

MessageBox::MessageBox(QWidget *parent /*=0*/)
 : QMessageBox(parent)
{
}

MessageBox::~MessageBox()
{
}

void MessageBox::ErrorMessage(const QString &message)
{
  QMessageBox::critical(0, qApp->applicationName(), message);
}

void MessageBox::WarnMessage(const QString &message)
{
  QMessageBox::warning(0, qApp->applicationName(), message);
}

void MessageBox::InfoMessage(const QString &message)
{
  QMessageBox::information(0, qApp->applicationName(), message);
}

