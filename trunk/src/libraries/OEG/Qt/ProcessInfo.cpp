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

QString ProcessInfo::processName()
{
  return m_process_name;
}

void ProcessInfo::setProcessId(unsigned long int pid)
{
  m_process_id = pid;
}

int ProcessInfo::processId()
{
  return m_process_id;
}

void ProcessInfo::setParentProcessId(unsigned long pid)
{
  m_parent_process_id = pid;
}

int ProcessInfo::parentProcessId()
{
  return m_parent_process_id;
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

