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

#include <QDebug>
#include <QtPlugin>
#include <QString>
#include <QWidget>

#include "DesktopPlugin.h"
#include "Widget.h"

QWidget *DesktopPlugin::createGUI(QWidget *parent)
{
  m_gui = new Widget(parent);

  return m_gui;
}

QString DesktopPlugin::name() const
{
  return "Clock";
}

void DesktopPlugin::startPlugin()
{
}

void DesktopPlugin::stopPlugin()
{
}

Q_EXPORT_PLUGIN2(oegDesktopPlugin, DesktopPlugin);

