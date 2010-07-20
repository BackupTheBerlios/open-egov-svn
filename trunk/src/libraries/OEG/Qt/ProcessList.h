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
    ~ProcessList();

    void update();
    unsigned long int numberOfProcesses() const;

  private slots:

  protected:
    void printError(const QString &funName);
    void clearLists();

    bool searchProcessModules(unsigned long int pid);
    bool searchProcessThreads(unsigned long int pid);

  protected:
    QList<ModuleInfo *>   m_module_list;
    QList<ProcessInfo *>  m_process_list;
    QList<ThreadInfo *>   m_thread_list;
};

}}

