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

#include <OEG/Common.h>

#include <QObject>
#include <QString>

namespace OEG { namespace Qt {

class ModuleInfo : public QObject
{
  Q_OBJECT

  public:
    ModuleInfo(QObject *parent = 0);

    void setProcessId(unsigned long pid);
    int processId();

    void setModuleName(const QString &name);
    QString moduleName();

    void setModulePath(const QString &path);
    QString modulePath();

    void setBaseAddress(unsigned char *address);
    // QString(" Base address  = 0x%08X").arg((DWORD) me32.modBaseAddr, 0, 16);
    void setModuleSize(unsigned long size);
    void setRefCount(unsigned long count);

  protected:
    unsigned long  m_process_id;
    QString        m_module_name;
    QString        m_module_path;
    unsigned char *m_base_address;  // valid only in the context of the process specified by owning process.
    unsigned long  m_module_size;
    unsigned long  m_ref_count;
};

}}

