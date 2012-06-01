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

#include <OEG/Qt/ToolProvider.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QStringList>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_list_widget = new QTreeWidget(this);
  m_list_widget->setRootIsDecorated(false);
  m_list_widget->setHeaderLabels(QStringList() << "Applications" << "State");
  m_list_widget->setColumnCount(2);

  setCentralWidget(m_list_widget);

  QTreeWidgetItem *item = addNewItemToList("Test");
  addNewItemToList("123");
  addNewItemToList("456");

  m_list_widget->setCurrentItem(item);
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(_("&File"));
  fileMenu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createDockWidgets()
{
}

QTreeWidgetItem *MainWindow::addNewItemToList(const QString &title)
{
  QTreeWidgetItem *item = new QTreeWidgetItem(m_list_widget, QStringList() << "title" << "-");
  //QString("item: %1").arg(i)

  //item.append(new QTreeWidgetItem();
  //m_list_widget->insertTopLevelItems(0, items);
  //QTreeWidgetItem *cities = new QTreeWidgetItem(treeWidget);
  //item->setText(0, _("xx"));

  return item;
}

