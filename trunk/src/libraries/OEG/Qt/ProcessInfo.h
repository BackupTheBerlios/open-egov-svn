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

namespace OEG { namespace Qt {

class ProcessInfo : public QObject
{
  Q_OBJECT

  public:
    ProcessInfo(QObject *parent = 0);
    ~ProcessInfo();

    void setProcessName(const QString &name);
    QString processName();

    void setProcessId(unsigned long int pid);
    int processId();

    void setParentProcessId(unsigned long pid);
    int parentProcessId();

    void setThreadCount(unsigned long count);
    void setPriorityClassBase(long base);
    void setPriorityClass(unsigned long pc);

  protected:
    QString        m_process_name;
    unsigned long  m_process_id;
    unsigned long  m_parent_process_id;
    unsigned long  m_thread_count;
    long           m_priority_class_base;
    unsigned long  m_priority_class;
};

}}

