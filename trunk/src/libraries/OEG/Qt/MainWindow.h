// $Id$

#pragma once

#include <QMainWindow>
#include <QList>

class QAction;

namespace OEG { namespace Qt {

class ToolProvider;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~MainWindow();

  protected:
    void createActions();
    void createDockWidgets();
    void createMenus();
    void createStatusBar();
    void createToolBars();
    void createToolProvider();

  private:

  protected:
    ToolProvider      *m_tool_provider;
    QList<QAction *>   m_actions;
};

}}

