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

#include <OEG/Common.h>

#include <QWidget>
#include <QString>

#include "PluginInterface.h"

class Plugin : public QObject, public PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginInterface)

  public:
    virtual ~Plugin() {}

    QString pluginName() const;
    QString pluginTitle() const;
    QString pluginApplicationName() const;
    QString pluginApplicationTitle() const;
    unsigned int pluginVersion() const;
    QString pluginDate() const;

    virtual QWidget *pluginGUI(QWidget *parent = 0);

    void pluginStart();
    void pluginStop();

  private:
    QWidget *m_gui;
};

