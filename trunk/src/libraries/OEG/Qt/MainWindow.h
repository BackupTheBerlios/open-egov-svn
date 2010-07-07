// $Id$

#pragma once

#include <QMainWindow>

namespace OEG { namespace Qt {

class ToolProvider;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~MainWindow();

  protected:


  private:

  protected:
    ToolProvider  *m_tool_provider;
};

}}

