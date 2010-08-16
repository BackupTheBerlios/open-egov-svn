// $Id$
//
// G.A.S.I. Libraries Pack: Qt Extension Library
// Copyright (C) 2005-2008 by Gerrit M. Albrecht
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
#include <QApplication>

#include <GASI/Qt/MessageBox.h>

using namespace GASI::Qt;

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

