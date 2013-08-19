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

#include <OEG/Qt/TabbedMenuBar.h>
#include <OEG/Qt/Application.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QProcess>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <QLatin1String>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileInfoList>
#include <QLineEdit>
#include <QHash>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  QWidget *board = new QWidget(this);

  setCentralWidget(board);

  createAll();

  connect(board, SIGNAL(customContextMenuRequested(const QPoint &)),
          this,  SLOT(onBoardCustomContextMenuRequested(const QPoint &)));
  //connect(board, SIGNAL(boardChanged()),
  //        this,  SLOT(updateStatusBar()));
}

void MainWindow::commonSettings()
{
}

void MainWindow::onBoardCustomContextMenuRequested(const QPoint &pos)
{
  Q_UNUSED(pos);

  qWarning() << "MainWindow::onBoardCustomContextMenuRequested()";

  QMenu menu(this);

  //act->setEnabled((!model->rowCount()) ? false : true );
  menu.addAction("test", this, SLOT(testslot()));

  menu.exec(QCursor::pos());
}

void MainWindow::updateStatusBar()
{
  m_x->setText(_("xx:") + QLatin1String(" ") +
    QString::number(12345));
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

  QAction *action;
  QString s;

  action = standardAction(New);
  action->setText(_("&New Game"));
  s = _("Starts a new game.");
  action->setToolTip(s);
  action->setStatusTip(s);
  connect(action, SIGNAL(triggered()),
          this,   SLOT(newGameAction()));
}

void MainWindow::createStatusBar()
{
  m_x = new QLabel("Moves: 0000");
  m_x->setMinimumSize(m_x->sizeHint());
  m_x->setAlignment(Qt::AlignCenter);
  m_x->setToolTip(_("xxx."));
  statusBar()->addPermanentWidget(m_x);

  updateStatusBar();

  OEG::Qt::MainWindow::createStatusBar();
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = getStandardMenu(FileMenu);
  menu->addAction(standardAction(New));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(SettingsMenu);
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()), this, SLOT(commonSettings()));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(New));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createTabbedMenuBar()
{
}

