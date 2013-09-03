// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

#include <QDir>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent), m_current_case_id(0)
{
  setWindowIcon(QIcon("icon.png"));

  QWidget *w = new QWidget(this);

  setCentralWidget(w);

  createAll();

  OEG::Qt::Application *oegApp = dynamic_cast<OEG::Qt::Application *>(qApp);
  m_db = QSqlDatabase::addDatabase("QSQLITE", oegApp->baseName() + ".db");
  QString dbfile = oegApp->locateFile(oegApp->baseName() + ".db",
                                      OEG::Qt::Application::UserDatabase);
  m_db.setDatabaseName(QDir::toNativeSeparators(dbfile));

  if (! m_db.open()) {
    qWarning() << "Database not open:" << m_db.lastError().text();
    qWarning() << "File:" << dbfile;
  }

  addHistoryEntry(HEID_DATABASE_OPENED);
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

  QAction *action;
  QString s;

  action = standardAction(New);
  action->setText(_("&New case..."));
  s = _("Create a new case.");
  action->setToolTip(s);
  action->setStatusTip(s);
  connect(action, SIGNAL(triggered()),
          this,   SLOT(newDataAction()));

  action = standardAction(Open);
  action->setText(_("&Open case..."));
  s = _("Open existing case.");
  action->setToolTip(s);
  action->setStatusTip(s);

  action = standardAction(Close);
  action->setText(_("&Close case..."));
  s = _("Close current case.");
  action->setToolTip(s);
  action->setStatusTip(s);
  action->setEnabled(false);
}

void MainWindow::createStatusBar()
{
  OEG::Qt::MainWindow::createStatusBar();

  m_sb_file_count = new QLabel("12345");
  m_sb_file_count->setMinimumSize(m_sb_file_count->sizeHint());
  m_sb_file_count->setAlignment(Qt::AlignCenter);
  m_sb_file_count->setToolTip(_("File count."));
  statusBar()->addPermanentWidget(m_sb_file_count);

  m_sb_current_file = new QLabel("12345");
  m_sb_current_file->setMinimumSize(m_sb_current_file->sizeHint());
  m_sb_current_file->setAlignment(Qt::AlignCenter);
  m_sb_current_file->setToolTip(_("Current file."));
  statusBar()->addPermanentWidget(m_sb_current_file);

  updateStatusBar();
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
  menu->addAction(standardAction(Open));
  menu->addAction(standardAction(Close));
  menu->addSeparator();
  menu->addAction(standardAction(Print));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));
  menu->addSeparator();
  menu->addAction(standardAction(Delete));

  menu = menuBar()->addMenu(_("F&orms"));
  action = menu->addAction(_("&Select..."));
  connect(action, SIGNAL(triggered()), this, SLOT(selectForms()));

  menu = menuBar()->addMenu(_("&Law"));
  action = menu->addAction(_("&Select..."));
  connect(action, SIGNAL(triggered()), this, SLOT(selectLaw()));
  menu->addSeparator();
  action = menu->addAction(_("SchStG LSA (act)"));
  action = menu->addAction(_("SchStG LSA (administrative regulation)"));
  menu->addSeparator();
  action = menu->addAction(_("BGB"));
  action = menu->addAction(_("StGB"));
  // http://de.wikipedia.org/wiki/Nachbarrecht
  // http://www.landesrecht.sachsen-anhalt.de/jportal/?quelle=jlink&query=NachbG+ST&psml=bssahprod.psml&max=true&aiz=true
  action = menu->addAction(_("NbG ST"));


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
  toolbar->addAction(standardAction(Open));
  toolbar->addAction(standardAction(Close));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Print));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Cut));
  toolbar->addAction(standardAction(Copy));
  toolbar->addAction(standardAction(Paste));
  toolbar->addAction(standardAction(Delete));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::updateStatusBar()
{
}

QStringList MainWindow::catchwordList()
{
  return QStringList() << _("Conflict")                    // Streit.
                       << _("Insult")                      // Beleidigung.
                       << _("property line")               // Grundstücksgrenze.
                       << _("Neighbor")                    // Nachbar.
                       << _("Libel and slander");          // Verleumdung und üble Nachrede, Ehrverletzung
}

QStringList MainWindow::resultTypeId()
{
  return QStringList() << _("Successfully closed.")        // Erfolgreich geschlossen.
                       << _("Unsuccessfully closed.");     // Erfolglos geschlossen.
}

// List is in sync with enums in header file.

QStringList MainWindow::historyEntryId()
{
  return QStringList() << _("First consultation.")         // Erstes Gespräch - needed for statistics.
                       << _("Case opened.")                // Fall eröffnet.
                       << _("Paid due.")                   // Gebühr bezahlt.
                       << _("Served subpoena.")            // Vorladung zugestellt.
                       << _("Hearing.")                    // Verhandlung.
                       << _("Rehashing.")                  // Erneute Verhandlung.
                       << _("Case reopened.")              //
                       << _("Served protocol copy.")       //
                       << _("Case waits.")                 //
                       << _("Note.")                       // Eine Notiz zu den Akten nehmen.
                       << _("Consultation.")               // Gespräch, außerhalb des Verfahrens (danach).
                       << _("Refunded money.")             // Geld zurückerstattet.
                       << _("Case closed.")                // Fall geschlossen.
                       << _("Database opened.")            // Datenbank geöffnet, application started.
                       << _("Case archived.")              // Fall wurde archiviert.
                       << _("Case viewed.");               // Fall angesehen (Revisionsfähigkeit).
}

void MainWindow::addHistoryEntry(const int historyEntryId, const QString &value /*=""*/)
{
  QSqlQuery query(m_db);

  if (! query.prepare("INSERT INTO histories (id,case_id,current_date,value,history_entry_id) "
                      "VALUES (NULL,:case_id,datetime('now'),:value,:history_entry_id)")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":value",            value);
  query.bindValue(":case_id",          m_current_case_id);
  query.bindValue(":history_entry_id", historyEntryId);
  
  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return;
  }
}

void MainWindow::selectForms()
{
}

void MainWindow::selectLaw()
{
}

