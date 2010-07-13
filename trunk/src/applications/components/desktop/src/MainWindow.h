// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>

#include <QWidget.h>

class QVBoxLayout;
class QMenuBar;
class QMenu;
class QAction;
class QCloseEvent;

class DesktopWidget : public QWidget //OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    DesktopWidget(QWidget *parent = 0);

  private slots:
    void about();
    void helpViewer();

  private:
    void createActions();
    void createMenus();

  protected:
    void closeEvent(QCloseEvent *event);

  protected:
    QVBoxLayout *m_layout;
    QMenuBar    *m_menubar;
    QMenu       *m_menu_file;
    QMenu       *m_menu_help;
    QAction     *m_action_exit;
    QAction     *m_action_help;
    QAction     *m_action_about_app;
    QAction     *m_action_about_qt;
};

