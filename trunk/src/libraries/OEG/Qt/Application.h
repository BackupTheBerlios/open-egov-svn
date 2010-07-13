// $Id$

#pragma once

#include <QApplication>
#include <QString>
#include <QStringList>

#include <QDebug>

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

