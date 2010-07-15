// $Id$

#pragma once

#include <OEG/Common.h>

#include <QApplication>
#include <QString>
#include <QStringList>

#include <QDebug>

#define MODULE_INFO(txt) static const char oeg_ident[] =  \
  "   Open eGovernment (www.open-egov.de), " txt "   "; \
  const char *oeg_ident_x = oeg_ident;

namespace OEG { namespace Qt {

class Application : public QApplication
{
  Q_OBJECT

  public:
    Application(int &argc, char *argv[]);
    virtual ~Application();

    static void runComponent(const QString &cmd);
    static void runComponent(const QString &cmd, const QStringList &arguments);

  protected:


  protected:

};

}}

