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

#include <OEG/Common.h>

#include <QObject>
#include <QString>

class World : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString      m_name        READ name        WRITE setName)
  Q_PROPERTY(QString      m_host        READ host        WRITE setHost)
  Q_PROPERTY(unsigned int m_port        READ port        WRITE setPort)
  Q_PROPERTY(QString      m_description READ description WRITE setDescription)
  Q_PROPERTY(QString      m_homepage    READ homepage    WRITE setHomepage)

  public:
    World();

    void setName(const QString &name);
    QString name() const;

    void setHost(const QString &host);
    QString host() const;

    void setPort(unsigned int port);
    unsigned int port() const;

    void setDescription(const QString &description);
    QString description() const;

    void setHomepage(const QString &homepage);
    QString homepage() const;

  protected:
    unsigned int m_id;

    QString      m_name;
    QString      m_host;
    unsigned int m_port;
    QString      m_description;
    QString      m_homepage;
};

