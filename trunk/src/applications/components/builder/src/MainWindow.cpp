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
#include <QFontMetrics>

#include <iostream>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent), m_worker_process(0), m_package_filter(0)
{
  setWindowIcon(QIcon("icon.png"));

  m_table_widget = new QTableWidget(this);
  m_table_widget->setColumnCount(6);                       // Always adjust to number of columns below.
  m_table_widget->setHorizontalHeaderLabels(QStringList()
    << _("Package")
    << _("Version")
    << _("Flags")
    << _("W")
    << _("I")
    << _("A"));
  m_table_widget->verticalHeader()->hide();
  m_table_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  m_table_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_table_widget->setShowGrid(true);
  m_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_table_widget->setAlternatingRowColors(false);  // into the settings.
  m_table_widget->setContextMenuPolicy(Qt::CustomContextMenu);

  QHeaderView *horizontalHeader = m_table_widget->horizontalHeader();
  horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
  horizontalHeader->setSectionResizeMode(2, QHeaderView::Stretch);
  horizontalHeader->setSectionResizeMode(3, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(4, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(5, QHeaderView::ResizeToContents);

  QTableWidgetItem *headerItem;
  headerItem = m_table_widget->horizontalHeaderItem(0);
  if (headerItem) {
    headerItem->setToolTip(_("Name of the package"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }
  headerItem = m_table_widget->horizontalHeaderItem(1);
  if (headerItem) {
    headerItem->setToolTip(_("Version number"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }
  headerItem = m_table_widget->horizontalHeaderItem(2);
  if (headerItem) {
    headerItem->setToolTip(_("Flags you may select"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }
  headerItem = m_table_widget->horizontalHeaderItem(3);
  if (headerItem) {
    headerItem->setToolTip(_("The package is functional and works"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }
  headerItem = m_table_widget->horizontalHeaderItem(4);
  if (headerItem) {
    headerItem->setToolTip(_("The package is currently installed"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }
  headerItem = m_table_widget->horizontalHeaderItem(5);
  if (headerItem) {
    headerItem->setToolTip(_("The package is archived as binary"));
    headerItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  }

  setCentralWidget(m_table_widget);

  createAll();

  connect(m_table_widget, SIGNAL(customContextMenuRequested(const QPoint &)),
          this,           SLOT(onTableCustomContextMenuRequested(const QPoint &)));
  connect(m_table_widget, SIGNAL(itemSelectionChanged()),
          this,           SLOT(updateStatusBar()));

  updatePackageList();

  m_table_widget->setVisible(false);
  m_table_widget->resizeColumnsToContents();
  m_table_widget->setVisible(true);

  m_table_widget->setSortingEnabled(true);
  m_table_widget->sortItems(0, Qt::AscendingOrder);
  m_table_widget->setUpdatesEnabled(true);
}

void MainWindow::updatePackageList()
{
  if (! m_table_widget)
    return;

  QDir dir(dynamic_cast<OEG::Qt::Application *>(qApp)->standardDirectory(OEG::Qt::Application::Data));
  dir.cd("instructions");
  //QMessageBox::information(this, "", dir.absolutePath(), QMessageBox::Ok);

  QStringList filters;
  filters << "*.xml";
  dir.setNameFilters(filters);
  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
  dir.setSorting(QDir::Name | QDir::Reversed);

  m_table_widget->setUpdatesEnabled(false);
  m_table_widget->clearContents();   // "the table dimensions stay the same".
  m_table_widget->setRowCount(0);
  m_table_widget->setSortingEnabled(false);

  QHeaderView *horizontalHeader = m_table_widget->horizontalHeader();
  horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(1, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(2, QHeaderView::Stretch);
  horizontalHeader->setSectionResizeMode(3, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(4, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(5, QHeaderView::ResizeToContents);

  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); i++) {
    QFileInfo fileInfo = list.at(i);
    //qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));

    const int currentRow = m_table_widget->rowCount();
    m_table_widget->setRowCount(currentRow + 1);

    QTableWidgetItem *item;
    QHash<QString, QVariant> hash;
    hash["filename"] = fileInfo.fileName();
    hash["filesize"] = fileInfo.size();

    item = new QTableWidgetItem(fileInfo.fileName());
    item->setData(Qt::UserRole, hash);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    m_table_widget->setItem(currentRow, 0, item);

    item = new QTableWidgetItem("x.y");
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    m_table_widget->setItem(currentRow, 1, item);

    item = new QTableWidgetItem("");
    m_table_widget->setItem(currentRow, 2, item);

    item = new QTableWidgetItem();
    item->setCheckState(Qt::Unchecked);
    m_table_widget->setItem(currentRow, 3, item);

    item = new QTableWidgetItem();
    item->setCheckState(Qt::Checked);
    m_table_widget->setItem(currentRow, 4, item);

    item = new QTableWidgetItem();
    item->setCheckState(Qt::Checked);
    m_table_widget->setItem(currentRow, 5, item);
  }

  m_table_widget->clearSelection(); // TODO
  m_table_widget->clearFocus();

  m_table_widget->setSortingEnabled(true);
  m_table_widget->sortItems(0, Qt::AscendingOrder);
  m_table_widget->setUpdatesEnabled(true);

#if 0
  QFontMetrics fm(m_table_widget->font());

  for (int row=0 ; row<m_table_widget->rowCount(); row++) {
    int maxWidth = 0;

    QString text = m_table_widget->item(row, 0)->text();

    if (fm.width(text) > maxWidth)
      maxWidth = fm.width(text);

    QHeaderView *hv = m_table_widget->horizontalHeader();
    if (maxWidth > hv->sectionSize(row)) {
      //horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
      //hv->resizeSection(row, maxWidth * 1.5);
    }
  }
#endif

  updateStatusBar();
}

void MainWindow::clearEnvironment()
{
}

void MainWindow::installRequiredPackages()
{
}

void MainWindow::compilePackage()
{
}

void MainWindow::createBinaryArchive()
{
}

void MainWindow::newPackage()
{
  //CreatePackageDialog dialog;

  //if (dialog.exec()) {

  //}
}

void MainWindow::editPackage()
{
}

void MainWindow::overlayPackage()
{
}

void MainWindow::openCommandLineInterface()
{
}

void MainWindow::commonSettings()
{
}

void MainWindow::onTableCustomContextMenuRequested(const QPoint &pos)
{
  Q_UNUSED(pos);

  qWarning() << "MainWindow::onTableCustomContextMenuRequested()";

  QMenu menu(this);

  //act->setEnabled((!model->rowCount()) ? false : true );
  menu.addAction("test", this, SLOT(testslot()));

  menu.exec(QCursor::pos());
}

// Needs to be called if the number of packages changes (manually, because there
// is no rowCountChanged signal for QTableWidget) and if the selection changes.

void MainWindow::updateStatusBar()
{
  m_number_of_packages->setText(_("Packages:") + QLatin1String(" ") +
    QString::number(m_table_widget->rowCount()));
  m_number_of_selected_rows->setText(_("Selected:") + QLatin1String(" ") +
    QString::number(m_table_widget->selectedItems().count() / m_table_widget->columnCount()));
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

  QAction *action;
  QString s;

  action = standardAction(Reload);
  action->setText(_("Update package list"));
  s = _("Reloads the list of packages.");
  action->setToolTip(s);
  action->setStatusTip(s);
  connect(action, SIGNAL(triggered()),
          this,   SLOT(updatePackageList()));
}

void MainWindow::createStatusBar()
{
  m_number_of_packages = new QLabel("Packages: 0000");
  m_number_of_packages->setMinimumSize(m_number_of_packages->sizeHint());
  m_number_of_packages->setAlignment(Qt::AlignCenter);
  m_number_of_packages->setToolTip(_("The number of packages."));
  statusBar()->addPermanentWidget(m_number_of_packages);

  m_number_of_selected_rows = new QLabel("Selected: 0000");
  m_number_of_selected_rows->setMinimumSize(m_number_of_selected_rows->sizeHint());
  m_number_of_selected_rows->setAlignment(Qt::AlignCenter);
  m_number_of_selected_rows->setToolTip(_("The number of currently selected packages."));
  statusBar()->addPermanentWidget(m_number_of_selected_rows);

  updateStatusBar();

  OEG::Qt::MainWindow::createStatusBar();
}

void MainWindow::createMenus()
{
  QMenu   *menu;
  QAction *action;

  menu = menuBar()->addMenu(_("&File"));
  menu->addAction(standardAction(Reload));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = menuBar()->addMenu(_("&Build"));
  action = menu->addAction(_("&Clear environment"));
  connect(action, SIGNAL(triggered()), this, SLOT(clearEnvironment()));
  action = menu->addAction(_("Install &required packages"));
  connect(action, SIGNAL(triggered()), this, SLOT(installRequiredPackages()));
  action = menu->addAction(_("&Compile package"));
  connect(action, SIGNAL(triggered()), this, SLOT(compilePackage()));
  action = menu->addAction(_("Create binary &archive"));
  connect(action, SIGNAL(triggered()), this, SLOT(createBinaryArchive()));

  menu = menuBar()->addMenu(_("&Instructions"));
  action = menu->addAction(_("New package..."));
  connect(action, SIGNAL(triggered()), this, SLOT(newPackage()));
  action = menu->addAction(_("Edit package..."));
  connect(action, SIGNAL(triggered()), this, SLOT(editPackage()));
  action = menu->addAction(_("Overlay package..."));
  connect(action, SIGNAL(triggered()), this, SLOT(overlayPackage()));
  menu->addSeparator();
  action = menu->addAction(_("Open Command Line Interface"));
  connect(action, SIGNAL(triggered()), this, SLOT(openCommandLineInterface()));

  menu = menuBar()->addMenu(_("&Settings"));
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()), this, SLOT(commonSettings()));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Reload));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));

  QLabel *l;

  l = new QLabel(_("&Filter:"));
  m_package_filter = new QLineEdit();
  l->setBuddy(m_package_filter);
  toolbar->addWidget(l);
  toolbar->addWidget(m_package_filter);

  connect(m_package_filter, SIGNAL(textChanged(const QString &)),
          this,             SLOT(filterTextChanged(const QString &)));
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::processInit()
{
  if (! m_worker_process) {
    m_worker_process = new QProcess();
  }

  m_worker_process->setWorkingDirectory(QCoreApplication::applicationDirPath());

  connect(m_worker_process, SIGNAL(readyRead()),   this, SLOT(processReadStdOut()));
  connect(m_worker_process, SIGNAL(started()),     this, SLOT(processStarted()));
  connect(m_worker_process, SIGNAL(finished(int)), this, SLOT(processFinished(int)));

  m_worker_process->start("");
}

void MainWindow::processReadStdOut()
{
  std::cout << "Standard Output: "
            << QString(m_worker_process->readAllStandardOutput()).toUtf8().constData()
            << std::endl;
}

void MainWindow::processStarted()
{
  std::cout << "Process started." << std::endl;
}

void MainWindow::processFinished(int signal)
{
  std::cout << "Process finished: " << signal << std::endl;
}

void MainWindow::filterTextChanged(const QString &text)
{
}

