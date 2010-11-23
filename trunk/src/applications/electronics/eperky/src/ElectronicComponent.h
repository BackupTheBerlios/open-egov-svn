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

#pragma once

#include <QDate>
#include <QList>
#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QByteArray;
class QFile;
QT_END_NAMESPACE

class ElectronicComponent : public QObject
{
  Q_OBJECT

  public:
    enum ComponentType {
      Circuit,
      Resistor,
      Capacitor,
      ElectrolyticCapacitor,
      Diode,
      Transistor,
      FieldEffectTransistor,   // http://www.linguee.de/deutsch-englisch/search?sourceoverride=none&source=auto&query=transistor
      VoltageSource,
      Lamp
    };

    enum ComponentPackaging {
      xxx
    };

  public:
    ElectronicComponent(QObject *parent = 0);

  public:                           // TODO: Change and fix this class, if everything works.
    QString         m_name;
    long long int   m_type;
    QList<QString>  m_electrical_connections;

    QString         m_manufacturer_name;
    QDate           m_last_seen;
    unsigned int    m_manufacturer_id;
    QString         m_order_number;
    unsigned int    m_price;
    unsigned int    m_minimum_order_quantity;
};

