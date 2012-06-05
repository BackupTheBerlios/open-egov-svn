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

#pragma once

#include <QtPlugin>

#include <QWidget>
#include <QString>
#include <QGraphicsItem>

class PluginInterface
{
  public:
    virtual ~PluginInterface() {}

    virtual QString pluginName() const = 0;
    virtual QString pluginTitle() const = 0;
    virtual QString pluginApplicationName() const = 0;
    virtual QString pluginApplicationTitle() const = 0;
    virtual unsigned int pluginVersion() const = 0;
    virtual QString pluginDate() const = 0;

    virtual QWidget *pluginGUI(QWidget *parent = 0) = 0;

    virtual void pluginStart() = 0;
    virtual void pluginStop() = 0;

  protected:

};

Q_DECLARE_INTERFACE(PluginInterface, "de.open-egov.Plugin.ePerky.PluginInterface/1.0");

