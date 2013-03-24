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

int ThreadInfo::processId()
{
  return m_process_id;
}

void ThreadInfo::setThreadId(unsigned long tid)
{
  m_thread_id = tid;
}

int ThreadInfo::threadId()
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

