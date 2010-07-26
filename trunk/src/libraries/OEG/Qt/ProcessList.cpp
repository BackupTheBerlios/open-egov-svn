// $Id$

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

#include <OEG/Common.h>
#include <OEG/Qt/ProcessList.h>
#include <OEG/Qt/ModuleInfo.h>
#include <OEG/Qt/ProcessInfo.h>
#include <OEG/Qt/ThreadInfo.h>

// MSDN: Snapshots of the System
// http://msdn.microsoft.com/en-us/library/ms686313%28v=VS.85%29.aspx
//
// MSDN: MODULEENTRY32 Structure
// http://msdn.microsoft.com/en-us/library/ms684225%28VS.85%29.aspx
//
// MSDN: PROCESSENTRY32 Structure
// http://msdn.microsoft.com/en-us/library/ms684839%28VS.85%29.aspx
//
// MSDN: THREADENTRY32 Structure
// http://msdn.microsoft.com/en-us/library/ms686735%28VS.85%29.aspx
//
// MSDN: QueryFullProcessImageName Function
// http://msdn.microsoft.com/en-us/library/ms684919%28v=VS.85%29.aspx
//
// MSDN: CreateToolhelp32Snapshot Function
// http://msdn.microsoft.com/en-us/library/ms682489%28v=VS.85%29.aspx

using namespace OEG::Qt;

ProcessList::ProcessList(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_module_list.clear();
  m_process_list.clear();
  m_thread_list.clear();

  setDebugPrivileges(true);
}

ProcessList::~ProcessList()
{
  clearLists();
}

void ProcessList::clearLists()
{
  while (! m_module_list.isEmpty())
    delete m_module_list.takeFirst();
  while (! m_process_list.isEmpty())
    delete m_process_list.takeFirst();
  while (! m_thread_list.isEmpty())
    delete m_thread_list.takeFirst();
}

void ProcessList::update()
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  clearLists();

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    printError("CreateToolhelp32Snapshot (of processes)");
    return;
  }

  pe32.dwSize = sizeof(PROCESSENTRY32);          // Set the size of the structure before using it.
  if (! Process32First(hProcessSnap, &pe32)) {   // Retrieve information about the first process.
    printError("Process32First");                // show cause of failure
    CloseHandle(hProcessSnap);                   // clean the snapshot object
    return;
  }

  // Now walk the snapshot of processes, and display information about each process.
  do {
    ProcessInfo *info = new ProcessInfo();
    if (! info) {
      CloseHandle(hProcessSnap);
      return;
    }

    // The name of the executable file for the process. To retrieve the
    // full path to the executable file, call the "Module32First" function
    // and check the szExePath member of the MODULEENTRY32 structure that
    // is returned. You must call the "QueryFullProcessImageName" function
    // to retrieve the full path of the executable file for a 64-bit process.

    info->setProcessName(QString::fromWCharArray(pe32.szExeFile));

    dwPriorityClass = 0;                                   // Retrieve the priority class.
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
    if (hProcess == NULL) {
      printError("OpenProcess");
    }
    else {
      dwPriorityClass = GetPriorityClass(hProcess);
      if (dwPriorityClass)
        info->setPriorityClass(dwPriorityClass);
      else
        printError("GetPriorityClass");
      CloseHandle(hProcess);
    }

    info->setProcessId(pe32.th32ProcessID);
    info->setParentProcessId(pe32.th32ParentProcessID);
    info->setThreadCount(pe32.cntThreads);
    info->setPriorityClassBase(pe32.pcPriClassBase);        // Base priority of any threads created by this process.

    searchProcessModules(pe32.th32ProcessID);              // List the modules associated with this process.
    searchProcessThreads(pe32.th32ProcessID);              // List the threads associated with this process.

    m_process_list.append(info);
  } while (Process32Next(hProcessSnap, &pe32));

  CloseHandle(hProcessSnap);
}

void ProcessList::printError(const QString &funName)
{
  DWORD errorCode = GetLastError();
  TCHAR message[256];
  TCHAR *p;

  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),           // Default language.
         message, 256, NULL);

  p = message;                                   // Trim the end of the line and terminate it with a null.
  while ((*p > 31) || (*p == 9))
    ++p;
  do {
    *p-- = 0;
  } while((p >= message) && ((*p == '.') || (*p < 33)));

  qDebug() << funName << " failed with error " << errorCode
           << "(" << QString::fromWCharArray(message) << ")";
}

bool ProcessList::searchProcessModules(unsigned long int pid)
{
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  // Take a snapshot of all modules in the specified process.
  hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
  if (hModuleSnap == INVALID_HANDLE_VALUE) {
    // For pid 4 (System) I get GetLastError() == 8 (not enough memory for this command).
    // qDebug() << "PID = " << QString::number(pid);
    printError("CreateToolhelp32Snapshot (of modules)");
    return false;
  }

  me32.dwSize = sizeof(MODULEENTRY32);

  if (! Module32First(hModuleSnap, &me32)) {               // Retrieve information about the first module.
    printError("Module32First");                           // Show the cause of failure.
    CloseHandle(hModuleSnap);                              // Free the snapshot object.
    return false;
  }

  // Now walk the module list of the process, and display information about each module.
  do {
    ModuleInfo *info = new ModuleInfo();
    if (! info) {
      CloseHandle(hModuleSnap);
      return false;
    }

    info->setProcessId(me32.th32ProcessID);
    info->setModuleName(QString::fromWCharArray(me32.szModule));
    info->setModulePath(QString::fromWCharArray(me32.szExePath));
    info->setBaseAddress(me32.modBaseAddr); // BYTE *  The base address of the module in the context of the owning process.
    info->setModuleSize(me32.modBaseSize);  // The size of the module, in bytes.
    info->setRefCount(me32.GlblcntUsage);   // Load count of the module, same as me32.ProccntUsage.

    m_module_list.append(info);
  } while(Module32Next(hModuleSnap, &me32));

  CloseHandle(hModuleSnap);

  return true;
}

bool ProcessList::searchProcessThreads(unsigned long int pid)
{
  HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
  THREADENTRY32 te32;

  hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);    // Take a snapshot of all running threads.
  if (hThreadSnap == INVALID_HANDLE_VALUE)
    return false;

  te32.dwSize = sizeof(THREADENTRY32);           // Fill in the size of the structure before using it.

  if (! Thread32First(hThreadSnap, &te32)) {     // Retrieve information about the first thread, and exit if unsuccessful.
    printError("Thread32First");                 // show cause of failure
    CloseHandle(hThreadSnap);                    // clean the snapshot object
    return false;
  }

  do {                                           // Display information about each thread associated with the specified process.
    if (te32.th32OwnerProcessID == pid) {
      ThreadInfo *info = new ThreadInfo();
      if (! info) {
        CloseHandle(hThreadSnap);
        return false;
      }

      info->setProcessId(pid);
      info->setThreadId(te32.th32ThreadID);
      info->setBasePriority(te32.tpBasePri);      // Kernel base priority level assigned to the thread (0-31, low-high).

      m_thread_list.append(info);
    }
  } while(Thread32Next(hThreadSnap, &te32));

  CloseHandle(hThreadSnap);

  return true;
}

int ProcessList::numberOfProcesses() const
{
  return m_process_list.size();
}

int ProcessList::numberOfModules(int processId) const
{
  int number = 0;

  for (int i=0; i<m_module_list.size(); i++) {
    if (m_module_list.at(i)->processId() == processId)
      number++;
  }

  return number;
}

int ProcessList::numberOfThreads(int processId) const
{
  int number = 0;

  for (int i=0; i<m_thread_list.size(); i++) {
    if (m_thread_list.at(i)->processId() == processId)
      number++;
  }

  return number;
}

ProcessInfo *ProcessList::processInfo(int processNumber)
{
  return m_process_list.at(processNumber);
}

ProcessInfo *ProcessList::processInfoById(int processId)
{
  ProcessInfo *pi;
  int size = m_process_list.size();

  for (int i=0; i<size; i++) {
    pi = m_process_list.at(i);
    if (pi->processId() == processId)
      return pi;
  }

  return 0;
}

ModuleInfo *ProcessList::moduleInfo(int processId, int moduleNumber)
{
  ModuleInfo *mi;
  int size = m_module_list.size();
  int number = -1;

  for (int i=0; i<size; i++) {
    mi = m_module_list.at(i);
    if (mi) {
      if (mi->processId() == processId) {
        number++;
        if (number == moduleNumber)
          return mi;
      }
    }
  }

  return 0;
}

ThreadInfo *ProcessList::threadInfo(int processId, int threadNumber)
{
  ThreadInfo *ti;
  int size = m_thread_list.size();
  int number = -1;

  for (int i=0; i<size; i++) {
    ti = m_thread_list.at(i);
    if (ti) {
      if (ti->processId() == processId) {
        number++;
        if (number == threadNumber)
          return ti;
      }
    }
  }

  return 0;
}

bool ProcessList::setDebugPrivileges(bool enable /*=true*/)
{
  HANDLE           token;
  LUID             luid;      // Locally unique identifier, used by the local system to identify the privilege.
  TOKEN_PRIVILEGES tp;
  LPCTSTR          privilege; // http://msdn.microsoft.com/en-us/library/aa375728(v=VS.85).aspx

  if (! OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
    printError("OpenProcessToken");
    return false;
  }

  privilege = L"SeDebugPrivilege";               // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
  if (! LookupPrivilegeValue(NULL, privilege, &luid)) {
    printError("LookupPrivilegeValue");
    CloseHandle(token);
    return false;
  }

  tp.PrivilegeCount           = 1;
  tp.Privileges[0].Luid       = luid;
  tp.Privileges[0].Attributes = (enable) ? SE_PRIVILEGE_ENABLED : 0;

  if (! AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), NULL, NULL)) {
    printError("AdjustTokenPrivileges");
    CloseHandle(token);
    return false;
  }

  if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
    qDebug() << "The token does not have the specified privilege.";
    return false;
  } 

  CloseHandle(token);
  return true;
}

// Called for every window. Posts WM_CLOSE to all windows with the
// correct processId.

BOOL CALLBACK KillAppEnumWindowsCallback(HWND hwnd, LPARAM processId)
{
  DWORD pid;

  GetWindowThreadProcessId(hwnd, &pid);

  if (pid == (DWORD)processId) {
    PostMessage(hwnd, WM_CLOSE, 0, 0);
  }

  return TRUE;
}

bool ProcessList::killProcess(int processId)
{
  if (processId <= 0)
    return false;

  setDebugPrivileges(true); // The security descriptor will be ignored, if we have debug privileges.

  HANDLE handle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, FALSE, processId);
  if (! handle) {
    QMessageBox::information(0, qApp->applicationName(), QString(_("No handle")));
    return false;
  }

  QMessageBox::information(0, QString("Titel"), QString("Text %1").arg(processId));

  //DWORD code = 0;
  //if (GetExitCodeProcess(handle, &code) == 0) {
  //  // Error 5 (Zugriff verweigert). Why?
  //  printError("GetExitCodeProcess");
  //  CloseHandle(handle);
  //  return false;
  //}
  //if (code == STILL_ACTIVE) {
  //QMessageBox::information(0, "", "");
  //}

  EnumWindows((WNDENUMPROC) KillAppEnumWindowsCallback, (LPARAM) processId);

  // Wait on the handle. If it signals, great. If it times out, then you kill it.

  if (WaitForSingleObject(handle, 1000) == WAIT_OBJECT_0) {
    CloseHandle(handle);
    QMessageBox::information(0, qApp->applicationName(), QString(_("Process closed successfully.")));
    return true;
  }

  if (TerminateProcess(handle, 0)) {
    CloseHandle(handle);
    QMessageBox::information(0, qApp->applicationName(), QString(_("Process terminated.")));
    return true;
  }

  CloseHandle(handle);

  return false;
}

// http://msdn.microsoft.com/en-us/library/ms686219%28VS.85%29.aspx

bool ProcessList::getPriority(int *priority, int processId /*=0*/)
{
  setDebugPrivileges(true); // The security descriptor will be ignored, if we have debug privileges.

  DWORD p;
  if (processId == 0) {
    p = GetPriorityClass(GetCurrentProcess());
  }
  else {
    if (processId < 0)
      return false;

    HANDLE handle = OpenProcess(PROCESS_SET_INFORMATION, FALSE, processId);
    if (! handle)
      return false;

    p = GetPriorityClass(handle);
    CloseHandle(handle);
  }

  switch (p) {
    case REALTIME_PRIORITY_CLASS:     *priority =  3; break;
    case HIGH_PRIORITY_CLASS:         *priority =  2; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: *priority =  1; break;
    case NORMAL_PRIORITY_CLASS:       *priority =  0; break;
    case BELOW_NORMAL_PRIORITY_CLASS: *priority = -1; break;
    case IDLE_PRIORITY_CLASS:         *priority = -2; break;
  }

  return true;
}

bool ProcessList::setPriority(int priority, int processId)
{
  if (processId <= 0)
    return false;

  setDebugPrivileges(true); // The security descriptor will be ignored, if we have debug privileges.

  HANDLE handle = OpenProcess(PROCESS_SET_INFORMATION, FALSE, processId); // PROCESS_ALL_ACCESS.
  if (! handle)
    return false;

  DWORD pri;
  if (priority >  3) priority =  3;
  if (priority < -2) priority = -2;
  switch (priority) {
    case  3: pri = REALTIME_PRIORITY_CLASS;     break; // Disallow it?
    case  2: pri = HIGH_PRIORITY_CLASS;         break;
    case  1: pri = ABOVE_NORMAL_PRIORITY_CLASS; break;
    case  0: pri = NORMAL_PRIORITY_CLASS;       break;
    case -1: pri = BELOW_NORMAL_PRIORITY_CLASS; break;
    case -2: pri = IDLE_PRIORITY_CLASS;         break;
  }

  if (SetPriorityClass(handle, pri) != 0) {
    CloseHandle(handle);
    return true;
  }

  CloseHandle(handle);
  return false;
}

