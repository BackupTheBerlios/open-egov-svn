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

#include <QDebug>
#include <QtPlugin>
#include <QString>
#include <QWidget>

#include "Plugin.h"
#include "Widget.h"

QString Plugin::pluginName() const
{
  return "resistor";
}

QString Plugin::pluginTitle() const
{
  return _("resistor");
}

QString Plugin::pluginApplicationName() const
{
  return "eperky";
}

QString Plugin::pluginApplicationTitle() const
{
  return _("ePerky");
}

unsigned int Plugin::pluginVersion() const
{
  return 1;
}

QString Plugin::pluginDate() const
{
  return "2012-06-06";
}

QWidget *Plugin::pluginGUI(QWidget *parent /*=0*/)
{
  m_gui = new Widget(parent);

  return m_gui;
}

void Plugin::pluginStart()
{
}

void Plugin::pluginStop()
{
}

Q_EXPORT_PLUGIN2(oegEperkyPlugin, Plugin);

