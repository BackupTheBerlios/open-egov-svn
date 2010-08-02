// $Id$

#include <OEG/Qt/TabWidget.h>

#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QLabel>
#include <QSplitter>
#include <QStatusBar>
#include <QAction>
#include <QIcon>

#include "MainWindow.h"
#include "Splitter.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  createAll();

  setWindowIcon(QIcon("icon.png"));

  m_splitter = new Splitter(this);
  m_splitter->setOrientation(Qt::Vertical);
  m_tabs = new OEG::Qt::TabWidget(this);
  m_tabs->addTab(new QWidget(this), _("No active game"));
  m_tabs->setTabsClosable(false);
  m_tabs->separateCloseTabButton(_("Close current tab."));
  m_splitter->addWidget(m_tabs);
  QLabel *label;
  label = new QLabel(this);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("input are\n(TODO)");
  label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  m_splitter->addWidget(label);
  m_splitter->setHandleWidth(20);
  setCentralWidget(m_splitter);
}

MainWindow::~MainWindow()
{
  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));

}

void MainWindow::createToolBars()
{
  QToolBar *fileToolBar = addToolBar(_("File"));

}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(_("Ready."));
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::setTitle(const QString &title)
{
  m_title = title;
}

QString MainWindow::title() const
{
  return m_title;
}

