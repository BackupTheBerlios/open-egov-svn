// $Id$

#include <OEG/Qt/Application.h>

#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>

DesktopWidget::DesktopWidget(QWidget *parent /*=0*/)
 : QWidget(0, Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnBottomHint)
 // OEG::Qt::MainWindow(parent, Qt::Desktop | Qt::FramelessWindowHint)
{
  setGeometry(parent->geometry());
  setFixedSize(parent->size());
  setBackgroundRole(QPalette::Window);

  m_menubar = new QMenuBar(this);

  m_layout = new QVBoxLayout;
  //m_layout->addWidget(m_menubar);
  m_layout->setMenuBar(m_menubar);
  setLayout(m_layout);

  createActions();
  createMenus();
}

void DesktopWidget::createActions()
{
  m_action_exit = new QAction(tr("E&xit"), this);
  m_action_exit->setShortcut(tr("Ctrl+Q"));
  m_action_exit->setStatusTip(tr("Exit the application"));
  connect(m_action_exit, SIGNAL(triggered()), this, SLOT(close()));

  m_action_help = new QAction(tr("&Help"), this);
  m_action_help->setStatusTip(tr("Open the help viewer"));
  connect(m_action_help, SIGNAL(triggered()), this, SLOT(helpViewer()));

  m_action_about_app = new QAction(tr("&About"), this);
  m_action_about_app->setStatusTip(tr("Show the application's About box"));
  connect(m_action_about_app, SIGNAL(triggered()), this, SLOT(about()));

  m_action_about_qt = new QAction(tr("About &Qt"), this);
  m_action_about_qt->setStatusTip(tr("Show the Qt library's About box"));
  connect(m_action_about_qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void DesktopWidget::createMenus()
{
  m_menu_file = m_menubar->addMenu(tr("&File"));
  //m_menu_file->addSeparator();
  m_menu_file->addAction(m_action_exit);

  m_menubar->addSeparator();

  m_menu_help = m_menubar->addMenu(tr("&Help"));
  m_menu_help->addAction(m_action_help);
  m_menu_help->addSeparator();
  m_menu_help->addAction(m_action_about_app);
  m_menu_help->addAction(m_action_about_qt);
}

void DesktopWidget::helpViewer()
{
  OEG::Qt::Application::runComponent("help-viewer", QStringList() << "index");
}

void DesktopWidget::about()
{
  OEG::Qt::Application::runComponent("about-dialog");
}

void DesktopWidget::closeEvent(QCloseEvent *event)
{
//    if (maybeSave()) {
//        writeSettings();
//       event->accept();
//    } else {
//        event->ignore();
//    }
}

