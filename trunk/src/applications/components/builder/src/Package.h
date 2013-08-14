// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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
#include <QDateTime>
#include <QString>

class Package : public QObject
{
  Q_OBJECT

  public:
    Package();

    inline QString filename() const { return m_filename; }
    inline void setFilename(const QString &filename) { m_filename = filename; }

  protected:

  private slots:

  private:
    QString   m_filename;

  public:
    QString   m_package_name;
    QString   m_package_version;
    QDateTime m_file_published;
    QDateTime m_file_downloaded;
};

