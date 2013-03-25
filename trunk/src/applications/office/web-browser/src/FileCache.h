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

#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QList>
#include <QHash>
#include <QByteArray>

#include "Downloader.h"

class FileCache : public QObject
{
  Q_OBJECT

  public:
    FileCache(QObject *parent = 0);

    QString    giveText(const QString &name);
    QByteArray giveBinary(const QString &name);

    void clear();
    void load();
    void save();

  private:
    bool                    m_loaded;                        // Only one load() call needed.
    QHash<QString, QString> m_data;
    QString                 m_file_name;
    QDateTime               m_valid_until;
    unsigned int            m_max_size_disk;                 // In bytes.
    unsigned int            m_max_size_memory;
    unsigned int            m_max_size_one_page;
    QString                 m_never_cache;
    //QString       m_url;
    //QByteArray    m_binary;
    //QStringList   m_http_header;
    static Downloader       m_downloader;
};

