// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/ProcessList.h>

#include <QString.h>
#include <QWidget.h>
#include <QList.h>

class OEG::Qt::ToolProvider;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createToolProvider() {};

  protected:
    OEG::Qt::ProcessList *m_processes;
};
