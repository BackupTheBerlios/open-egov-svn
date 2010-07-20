// $Id$

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <OEG/Common.h>
#include <OEG/Qt/ProcessInfo.h>

using namespace OEG::Qt;
using namespace Qt;

ProcessInfo::ProcessInfo(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_process_name = "";
  m_process_id   = 0L;
}

ProcessInfo::~ProcessInfo()
{
}

void ProcessInfo::setProcessName(const QString &name)
{
  m_process_name = name;
}

void ProcessInfo::setProcessId(unsigned long pid)
{
  m_process_id = pid;
}

void ProcessInfo::setParentProcessId(unsigned long pid)
{
  m_parent_process_id = pid;
}

void ProcessInfo::setThreadCount(unsigned long count)
{
  m_thread_count = count;
}

void ProcessInfo::setPriorityClassBase(long base)
{
  m_priority_class_base = base;
}

void ProcessInfo::setPriorityClass(unsigned long pc)
{
  m_priority_class = pc;
}

