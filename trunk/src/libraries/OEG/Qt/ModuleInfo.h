// $Id$

#pragma once

#include <OEG/Common.h>

#include <QObject>
#include <QString>

namespace OEG { namespace Qt {

class ModuleInfo : public QObject
{
  Q_OBJECT

  public:
    ModuleInfo(QObject *parent = 0);

    void setProcessId(unsigned long pid);
    int processId();

    void setModuleName(const QString &name);
    QString moduleName();

    void setModulePath(const QString &path);
    QString modulePath();

    void setBaseAddress(unsigned char *address);
    // QString(" Base address  = 0x%08X").arg((DWORD) me32.modBaseAddr, 0, 16);
    void setModuleSize(unsigned long size);
    void setRefCount(unsigned long count);

  protected:
    unsigned long  m_process_id;
    QString        m_module_name;
    QString        m_module_path;
    unsigned char *m_base_address;  // valid only in the context of the process specified by owning process.
    unsigned long  m_module_size;
    unsigned long  m_ref_count;
};

}}

