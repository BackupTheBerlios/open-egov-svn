// $Id$

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <OEG/Common.h>
#include <OEG/Qt/ModuleInfo.h>

using namespace OEG::Qt;
using namespace Qt;

ModuleInfo::ModuleInfo(QObject *parent /*=0*/)
 : QObject(parent)
{
  m_process_id   = 0;
  m_module_name  = "";
  m_module_path  = "";
  m_base_address = 0;
  m_module_size  = 0;
  m_ref_count    = 0;
}

void ModuleInfo::setProcessId(unsigned long pid)
{
  m_process_id = pid;
}

int ModuleInfo::processId()
{
  return m_process_id;
}

void ModuleInfo::setModuleName(const QString &name)
{
  m_module_name = name;
}

QString ModuleInfo::moduleName()
{
  return m_module_name;
}

void ModuleInfo::setModulePath(const QString &path)
{
  m_module_path = path;
}

QString ModuleInfo::modulePath()
{
  return m_module_path;
}

void ModuleInfo::setBaseAddress(unsigned char *address)
{
  m_base_address = address;
}

void ModuleInfo::setModuleSize(unsigned long size)
{
  m_module_size = size;
}

void ModuleInfo::setRefCount(unsigned long count)
{
  m_ref_count = count;
}

