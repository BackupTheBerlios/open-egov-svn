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
#include <QList>
#include <QString>

namespace OEG { namespace Qt {

class ModuleInfo;
class ProcessInfo;
class ThreadInfo;

class ProcessList : public QObject
{
  Q_OBJECT

  public:
    ProcessList(QObject *parent = 0);
    virtual ~ProcessList();

    int numberOfProcesses() const;
    int numberOfModules(int processId) const;
    int numberOfThreads(int processId) const;

    ProcessInfo *processInfo(int processNumber);
    ProcessInfo *processInfoById(int processId);
    ModuleInfo  *moduleInfo(int processId, int moduleNumber);
    ThreadInfo  *threadInfo(int processId, int threadNumber);

    bool setDebugPrivileges(bool enable = true);
    bool killProcess(int processId);
    bool getPriority(int *priority, int processId = 0);
    bool setPriority(int priority, int processId);

  public slots:
    void update();

  protected:
    void printError(const QString &funName);
    void clearLists();

    bool searchProcessModules(unsigned long int pid);
    bool searchProcessThreads(unsigned long int pid);

  protected:
    QList<ProcessInfo *>  m_process_list;
    QList<ModuleInfo *>   m_module_list;
    QList<ThreadInfo *>   m_thread_list;
};

}}

