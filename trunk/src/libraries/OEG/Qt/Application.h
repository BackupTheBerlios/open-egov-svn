// $Id$

#pragma once

#include <QApplication>

#include <QDebug>

namespace OEG { namespace Qt {

class Application : public QApplication
{
  Q_OBJECT

  public:
    Application(int &argc, char *argv[]);
    virtual ~Application();

  protected:


  protected:

};

}}

