// $Id$

#pragma once

#include <OEG/Common.h>

#include <QObject>

namespace OEG { namespace Qt {

class ThreadInfo : public QObject
{
  Q_OBJECT

  public:
    ThreadInfo(QObject *parent = 0);

    void setProcessId(unsigned long pid);
    int processId();

    void setThreadId(unsigned long tid);
    int threadId();

    void setBasePriority(long priority);
    long basePriority();

  protected:
    unsigned long  m_process_id;
    unsigned long  m_thread_id;
    long           m_priority;
};

}}

