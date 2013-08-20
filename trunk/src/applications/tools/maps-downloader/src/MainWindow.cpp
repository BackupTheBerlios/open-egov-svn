// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <QAction>
#include <QApplication>
#include <QLabel>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QListView>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QSplitter>
#include <QTabWidget>
#include <QTimer>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QSpacerItem>
#include <QLineEdit>
#include <QPushButton>
#include <QUrl>

#include <QDebug>

#include <OEG/Qt/MessageDialog.h>
#include <OEG/Qt/TabWidget.h>

#include "Thread.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent), m_working(false)
{
  setObjectName("MainWindow");
  setWindowIcon(QIcon("icon.png"));
  setWindowTitle(_("Maps Downloader"));

  m_map_type = new QComboBox(this);
  m_map_type->addItems(QStringList() << "Google Maps - Standard Maps"
                                     << "Google Maps - Satellite Maps"
                                     << "Google Maps - Terrain Maps"
                                     << "Google Maps - Hybrid Maps");
  m_map_type->setCurrentIndex(0);

  m_output = new QLabel("<h1>Progress</h1><p>Downloading...</p>");

  QWidget *top_area = new QWidget();                       // Can't add a layout to a splitter. Needed a dummy widget.
  QGridLayout *layout = new QGridLayout(top_area);         // Set parent in constructor or use widget->setLayout(layout).

  m_splitter = new QSplitter(this);
  m_splitter->setOrientation(Qt::Vertical);
  m_splitter->addWidget(top_area);
  m_splitter->addWidget(m_output);

  QLabel *map_type_label        = new QLabel(_("&Map provider and type:"), this);
  QLabel *left_lon_label        = new QLabel(_("&Left Longitude:"), this);
  QLabel *right_lon_label       = new QLabel(_("&Right Longitude:"), this);
  QLabel *top_lat_label         = new QLabel(_("&Top Latitude:"), this);
  QLabel *bottom_lat_label      = new QLabel(_("&Bottom Latitude:"), this);
  QLineEdit *left_lon_edit      = new QLineEdit(this);
  QLineEdit *right_lon_edit     = new QLineEdit(this);
  QLineEdit *top_lat_edit       = new QLineEdit(this);
  QLineEdit *bottom_lat_edit    = new QLineEdit(this);
  QLabel *save_path_label       = new QLabel(_("&Path to save:"), this);
  QLineEdit *save_path_edit     = new QLineEdit(this);
  QPushButton *save_path_button = new QPushButton("...", this);
  save_path_button->setFixedWidth(28);

  map_type_label->setBuddy(m_map_type);
  left_lon_label->setBuddy(left_lon_edit);
  right_lon_label->setBuddy(right_lon_edit);
  top_lat_label->setBuddy(top_lat_edit);
  bottom_lat_label->setBuddy(bottom_lat_edit);
  save_path_label->setBuddy(save_path_edit);

  layout->addWidget(map_type_label,        0, 0);
  layout->addWidget(m_map_type,            0, 1, 1, 3);
  layout->addItem(new QSpacerItem(10, 10), 1, 0);
  layout->addWidget(left_lon_label,        2, 0);
  layout->addWidget(left_lon_edit,         2, 1);
  layout->addItem(new QSpacerItem(10, 10), 2, 2);
  layout->addWidget(right_lon_label,       2, 3);
  layout->addWidget(right_lon_edit,        2, 4, 1, 2);
  layout->addWidget(top_lat_label,         3, 0);
  layout->addWidget(top_lat_edit,          3, 1);
  layout->addWidget(bottom_lat_label,      3, 3);
  layout->addWidget(bottom_lat_edit,       3, 4, 1, 2);
  layout->addItem(new QSpacerItem(10, 10), 4, 0);
  layout->addWidget(save_path_label,       5, 0);
  layout->addWidget(save_path_edit,        5, 1, 1, 4);
  layout->addWidget(save_path_button,      5, 5);

  setCentralWidget(m_splitter);

  connect(m_map_type, SIGNAL(currentIndexChanged(int)),
          this,       SLOT(mapTypeCurrentIndexChanged(int)));

  createAll();
}

MainWindow::~MainWindow()
{
  destroyRunningThreads();
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = menuBar()->addMenu(_("&File"));

  //menu->addAction(_("Update"), this, SLOT(updateAll()));
  m_action_start = menu->addAction(_("&Start"));
  connect(m_action_start, SIGNAL(triggered()),
          this,           SLOT(startThreads()));
  m_action_stop = menu->addAction(_("Stop"));
  connect(m_action_stop,  SIGNAL(triggered()),
          this,           SLOT(stopThreads()));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::mapTypeCurrentIndexChanged(int index)
{
  qDebug() << "MainWindow::mapTypeCurrentIndexChanged()" << index;
  //statusBar()->showMessage(_(""));

}

void MainWindow::addThread(const QUrl &path)
{
  Thread *thread = new Thread();

  connect(thread,  SIGNAL(threadFinished(Thread *)),
          this,    SLOT(threadFinished(Thread *)), Qt::QueuedConnection);


  thread->setPath(path);
  thread->start();

  m_threads.append(thread);
}

void MainWindow::threadFinished(Thread *thread)
{
  qDebug() << "MainWindow::threadFinished()";

  if (m_threads.count() <= 0)
    return;

  if (m_threads.contains(thread)) {
    m_threads.removeAll(thread);
  }
}

void MainWindow::stopRunningThreads()
{
  qDebug() << "MainWindow::stopRunningThreads()";

  if (m_threads.count() <= 0)
    return;

  Thread *thread;

  for (int i=0; i<m_threads.count(); i++) {
    thread = m_threads.at(i);
    if (thread) {
      if (thread->isRunning()) {
        thread->quit();
        thread->wait(2000);
      }

      if (! thread->isFinished()) {
        qDebug() << "Thread not finished.";
        continue;
      }

      delete thread;
    }
  }
}

void MainWindow::destroyRunningThreads()
{
  qDebug() << "MainWindow::destroyRunningThreads()";

  if (m_threads.count() <= 0)
    return;

  Thread *thread;

  while (! m_threads.isEmpty()) {
    thread = m_threads.takeFirst();
    if (thread) {
      thread->quit();
      thread->wait(1000);
      if (thread->isRunning())
        thread->terminate();
      delete thread;
     }
  }
}

void MainWindow::startThreads()
{
  addThread(QUrl("http://www.hhh.de/"));
}

void MainWindow::stopThreads()
{
  stopRunningThreads();
}

