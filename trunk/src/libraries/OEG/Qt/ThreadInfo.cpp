// $Id$

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <OEG/Common.h>
#include <OEG/Qt/ThreadInfo.h>

using namespace OEG::Qt;
using namespace Qt;

ThreadInfo::ThreadInfo(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_process_id = 0L;
  m_thread_id  = 0L;
  m_priority   = 0;
}

void ThreadInfo::setProcessId(unsigned long pid)
{
  m_process_id = pid;
}

unsigned long ThreadInfo::processId()
{
  return m_process_id;
}

void ThreadInfo::setThreadId(unsigned long tid)
{
  m_thread_id = tid;
}

unsigned long ThreadInfo::threadId()
{
  return m_thread_id;
}

void ThreadInfo::setBasePriority(long priority)
{
  m_priority = priority;
}

long ThreadInfo::basePriority()
{
  return m_priority;
}

