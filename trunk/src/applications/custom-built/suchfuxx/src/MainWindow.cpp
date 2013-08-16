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

#include <OEG/Qt/Application.h>
#include <OEG/Qt/TabbedMenuBar.h>

#include <QAction>
#include <QBrush>
#include <QDir>
#include <QDockWidget>
#include <QFile>
#include <QFont>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QFileSystemModel>
#include <QVBoxLayout>

#include <QDebug>

#include "FilePlanEntry.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setObjectName("MainWindow");
  setWindowTitle(_("SuchFuxx"));

  setWindowIcon(QIcon("icon.png"));

  createAll();

  m_tabs = new QTabWidget(this);
  m_tabs->setMinimumSize(200, 100);
  setCentralWidget(m_tabs);

  m_tab_fileplan  = new QWidget();
  m_tab_search    = new QWidget();
  m_tab_phonebook = new QWidget();
  m_fileplan      = new QTableWidget();
  QStringList list;
  QBrush fpiBrushNormal(Qt::NoBrush);
  QBrush fpiBrushHeader(Qt::cyan);
  QFont fpiFontNormal("Arial", 10);
  QFont fpiFontStrong("Arial", 10, QFont::Bold);

  QTableWidgetItem *table_item = 0;
  QString line;
  FilePlanEntry *entry;

  m_fileplan->setRowCount(0);
  m_fileplan->setColumnCount(3);
  m_fileplan->setHorizontalHeaderItem(0, new QTableWidgetItem("Aktenzeichen"));
  m_fileplan->setHorizontalHeaderItem(1, new QTableWidgetItem("Titel"));
  m_fileplan->setHorizontalHeaderItem(2, new QTableWidgetItem("Kommentar"));
  m_fileplan->verticalHeader()->hide();
  m_fileplan->setSelectionBehavior(QAbstractItemView::SelectRows);

  QDir dir(dynamic_cast<OEG::Qt::Application *>(qApp)->standardDirectory(OEG::Qt::Application::Data));
  qDebug() << dir.canonicalPath() + "/fileplan.txt";
  if (! dir.exists("fileplan.txt")) {
    qDebug() << "No fileplan file.";
    return;
  }

  QFile file(dir.canonicalPath() + "/fileplan.txt");
  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Could not open fileplan file.";
    return;
  }

  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  m_fileplan_list.clear();
  while (! stream.atEnd()) {
    line = stream.readLine().trimmed();

    if (line.length() == 0)
      continue;

    if (line.startsWith("Einzelfall:") ||
        line.startsWith("Einzelfälle:"))
      continue;

    list = line.split("\t");

    entry = new FilePlanEntry();
    if (entry) {
      int i = list.size();
      entry->setRefNo((i > 0) ? list.at(0).simplified() : "");
      entry->setTitle((i > 1) ? list.at(1).simplified() : "");
      entry->setComment((i > 2) ? list.at(2).simplified() : "");

      m_fileplan_list.append(entry);
    }
  }
  file.close();

  m_fileplan->setRowCount(m_fileplan_list.size());

  for (int i=0; i<m_fileplan_list.size(); i++) {
    entry = m_fileplan_list.at(i);

    table_item = new QTableWidgetItem();
    table_item->setText(entry->refNo());
    table_item->setTextAlignment(Qt::AlignLeft);
    //table_item->setForeground();
    //table_item->setBackground();
    table_item->setFont(fpiFontNormal);
    table_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
    m_fileplan->setItem(i, 0, table_item);

    table_item = new QTableWidgetItem();
    table_item->setText(entry->title());
    m_fileplan->setItem(i, 1, table_item);

    table_item = new QTableWidgetItem();
    table_item->setText(entry->comment());
    //table_item->setBackground(Qt::cyan);
    m_fileplan->setItem(i, 2, table_item);
  }

  //table_item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  //http://doc.trolltech.com/latest/qtablewidgetitem.html

  m_tabs->addTab(m_tab_fileplan,  _("Aktenplan"));
  m_tabs->addTab(m_tab_search,    _("Stichwortsuche"));
  m_tabs->addTab(m_tab_phonebook, _("Telefonbuch"));

  QGridLayout *layout;

  layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_fileplan, 0, 0);
  m_tab_fileplan->setLayout(layout);

  layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(new QLabel("1111"), 0, 0);
  layout->addWidget(new QLabel("2222"), 0, 1);
  layout->addWidget(new QLabel("3333"), 1, 0);
  layout->addWidget(new QLabel("4444"), 1, 1);
  m_tab_search->setLayout(layout);

  layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(new QWidget(), 0, 0);
  m_tab_phonebook->setLayout(layout);

#if 0
  QToolBox *m_toolbox = new QToolBox(m_dock_tree);
  m_toolbox->setMinimumSize(QSize(250, 100));
  QVBoxLayout *layout = new QVBoxLayout(m_dock_tree);
  layout->addWidget(m_dock_favorites);
  layout->addWidget(m_toolbox);
  m_dock_tree->setLayout(layout);

  m_toolbox->setCurrentIndex(0);

    QMenu* menu = new QMenu( this );
    menu->addAction( tr( "One" ) );

    QToolButton* popupButton1 = new QToolButton();
    popupButton1->setIcon( QIcon( ":/icons/new.png" ) );
    popupButton1->setMenu( menu );
    popupButton1->setPopupMode( QToolButton::InstantPopup );

    QToolButton* popupButton2 = new QToolButton();
    popupButton2->setIcon( QIcon( ":/icons/saveas.png" ) );
    popupButton2->setMenu( menu );
    popupButton2->setPopupMode( QToolButton::MenuButtonPopup );

    m_ui.toolBar->addSeparator();
    m_ui.toolBar->addWidget( popupButton1 );
    m_ui.toolBar->addWidget( popupButton2 );
#endif

  m_tabs->setCurrentIndex(0);

  //m_fileplan->resizeColumnsToContents();

  connect(m_fileplan, SIGNAL(itemSelectionChanged()),
          this,       SLOT(updateStatusBar()));

  QHeaderView *hv = m_fileplan->horizontalHeader();
  hv->setSectionResizeMode(0, QHeaderView::Interactive);
  hv->setSectionResizeMode(1, QHeaderView::Interactive);
  hv->setSectionResizeMode(2, QHeaderView::Interactive);
  hv->resizeSection(0, 60);
  hv->setStretchLastSection(true);
  //m_fileplan->setGridStyle(Qt::DotLine); // Qt::NoPen Qt::SolidLine

  QFontMetrics fm(m_fileplan->font());
  //int sectionLength = fm.width(s);

}

MainWindow::~MainWindow()
{
}

void MainWindow::updateStatusBar()
{
  QString s(_("Row: %1/%2"));
  s = s.arg(QString::number(m_fileplan->currentRow() + 1),
            QString::number(m_fileplan->rowCount()));
  m_sb_pos->setText(s);
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createStatusBar()
{
  m_sb_pos = new QLabel();
  m_sb_pos->setText("    ");
  m_sb_pos->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  m_sb_pos->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  statusBar()->addPermanentWidget(m_sb_pos);
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

  action = menu->addAction(_("Load ..."));
  connect(action, SIGNAL(triggered()), this, SLOT(loadFile()));

  action = menu->addAction(_("Save ..."));
  connect(action, SIGNAL(triggered()), this, SLOT(saveFile()));

  menu->addSeparator();
  menu->addAction(standardAction(Print));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(standardAction(Undo));
  menu->addAction(standardAction(Redo));
  menu->addSeparator();
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));
  menu->addSeparator();
  menu->addAction(standardAction(Delete));

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Exit));

  //QToolBox *m_toolbox = new QToolBox(this);
  //QToolButton* popupButton1 = new QToolButton();
  //popupButton1->setIcon( QIcon( ":/icons/new.png" ) );
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::loadFile()
{
}

void MainWindow::saveFile()
{
}

