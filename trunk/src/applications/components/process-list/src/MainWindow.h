// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/ProcessList.h>

#include <QList>
#include <QString>
#include <QWidget>

class QAction;
class QLabel;
class QTableWidget;
class QTimer;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void createActions();
    virtual void createStatusBar();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createToolProvider() {};

  public slots:
    void action_reload();
    void action_terminate_process();
    void action_open_process_dialog();
    void action_copy_details();

  protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

  protected:
    OEG::Qt::ProcessList *m_processes;
    QTableWidget         *m_table;
    QAction              *m_action_colorize;
    QLabel               *m_number_of_processes;
    QLabel               *m_current_time;
    QTimer               *m_timer;
};

