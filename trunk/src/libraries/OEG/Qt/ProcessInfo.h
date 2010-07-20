// $Id$

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
    void setProcessId(unsigned long pid);
    void setParentProcessId(unsigned long pid);
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

