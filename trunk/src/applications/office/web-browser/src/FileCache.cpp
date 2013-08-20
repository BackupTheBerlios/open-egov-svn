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

#include <QtCore>

#include "Downloader.h"
#include "MainWindow.h"
#include "WebPageFile.h"
#include "FileCache.h"

Downloader FileCache::m_downloader;

FileCache::FileCache(QObject *parent)
 : QObject(parent), m_loaded(false)
{
  m_max_size_memory =  10 * 1024 * 1024;                    //  10 MB.
  m_max_size_disk   = 100 * 1024 * 1024;                    // 100 MB.

  clear();
}

QString FileCache::giveText(const QString &name)
{
  m_downloader.downloadFile(name);

  connect(&m_downloader, SIGNAL(done()), this, SLOT(gotFile()));

  return "";
}

QByteArray FileCache::giveBinary(const QString &name)
{
  return QByteArray();
}

// Clears the whole cache and leaves nothing or only
// important, pre-selected (marked) objects.

void FileCache::clear()
{
}

// Loads valid cache data when starting the browser. The variable
// m_loaded is needed to avoid multiple loads() if there are
// multiple MainWindows, because Cache is a static object.

void FileCache::load()
{
  if (m_loaded)
    return;

  //

  m_loaded = true;
}

void FileCache::save()
{
}

