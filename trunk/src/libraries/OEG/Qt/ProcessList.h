// $Id$

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

