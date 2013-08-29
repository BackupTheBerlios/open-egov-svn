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

#include <OEG/Qt/TabbedMenuBar.h>
#include <OEG/Qt/Application.h>

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QLatin1String>
#include <QDir>
#include <QFile>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "AddWordDialog.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  m_locale_id_input  = 0;
  m_locale_id_output = 0;

  setWindowIcon(QIcon("icon.png"));

  loadSupportedLanguages();

  m_le_input  = new QLineEdit(this);
  m_te_output = new QTextEdit(this);
  m_te_output->setReadOnly(true);
  m_cb_input_language = new QComboBox(this);
  m_cb_input_language->setDuplicatesEnabled(false);
  m_cb_input_language->setEditable(false);
  m_cb_input_language->addItems(m_supported_languages);
  m_cb_input_language->setCurrentIndex(0);
  m_cb_output_language = new QComboBox(this);
  m_cb_output_language->setDuplicatesEnabled(false);
  m_cb_output_language->setEditable(false);
  m_cb_output_language->addItems(m_supported_languages);
  m_cb_output_language->setCurrentIndex(0);
  connect(m_cb_input_language, SIGNAL(currentIndexChanged(const QString &)),
          this, SLOT(currentIndexChangedInputCombobox(const QString &)));
  connect(m_cb_output_language, SIGNAL(currentIndexChanged(const QString &)),
          this, SLOT(currentIndexChangedOutputCombobox(const QString &)));

  m_la_input  = new QLabel(this);
  m_la_input->setBuddy(m_le_input);
  m_la_input->setText(_("&Input text:"));
  m_la_output = new QLabel(this);
  m_la_output->setBuddy(m_te_output);
  m_la_output->setText(_("&Translation:"));

  m_layout = new QGridLayout(this);
  m_layout->addWidget(m_la_input,           0, 0, 1, 1, 0);
  m_layout->addWidget(m_cb_input_language,  0, 1, 1, 1, 0);
  m_layout->addWidget(m_le_input,           1, 0, 1, 2, 0);
  m_layout->addWidget(m_la_output,          2, 0, 1, 1, 0);
  m_layout->addWidget(m_cb_output_language, 2, 1, 1, 1, 0);
  m_layout->addWidget(m_te_output,          3, 0, 1, 2, 0);

  setCentralLayout(m_layout);

  createAll();

  m_dictionary_db = QSqlDatabase::addDatabase("QSQLITE", "dictionary_db");
  QString dbfile = dynamic_cast<OEG::Qt::Application *>(qApp)->locateFile("dictionary.db",
                                                                          OEG::Qt::Application::UserDatabase);
  m_dictionary_db.setDatabaseName(QDir::toNativeSeparators(dbfile));

  if (! m_dictionary_db.open()) {
    qWarning() << "database not open:";
	QSqlError le = m_dictionary_db.lastError();
	qWarning() << le.text();
  }
}

void MainWindow::createActions()
{
  QString s;

  OEG::Qt::MainWindow::createActions();

  a_add_word = new QAction(_("&Add word ..."), this);
  a_translate = new QAction(_("&Translate"), this);
  a_toggle_direction = new QAction(_("Toggle &direction"), this);

  s = _("Add one or more words to the dictionary.");
  a_add_word->setToolTip(s);
  a_add_word->setStatusTip(s);
  s = _("Translate input text.");
  a_translate->setToolTip(s);
  a_translate->setStatusTip(s);
  s = _("Toggle translation direction.");
  a_toggle_direction->setToolTip(s);
  a_toggle_direction->setStatusTip(s);

  connect(a_add_word,         SIGNAL(triggered()),
          this,               SLOT(addWord()));
  connect(a_translate,        SIGNAL(triggered()),
          this,               SLOT(translate()));
  connect(a_toggle_direction, SIGNAL(triggered()),
          this,               SLOT(toggleDirection()));
}

void MainWindow::createStatusBar()
{
  OEG::Qt::MainWindow::createStatusBar();

  l_sb_word_count_global = new QLabel(_("Word count:") + QLatin1String(" ") + "00000");
  l_sb_word_count_global->setMinimumSize(l_sb_word_count_global->sizeHint());
  l_sb_word_count_global->setAlignment(Qt::AlignCenter);
  l_sb_word_count_global->setToolTip(_("The number of words available in all dictionaries."));
  statusBar()->addPermanentWidget(l_sb_word_count_global);

  l_sb_combinations_count = new QLabel(_("Dictionary size:") + QLatin1String(" ") + "00000");
  l_sb_combinations_count->setMinimumSize(l_sb_combinations_count->sizeHint());
  l_sb_combinations_count->setAlignment(Qt::AlignCenter);
  l_sb_combinations_count->setToolTip(_("The number of word combinations in the current dictionary."));
  statusBar()->addPermanentWidget(l_sb_combinations_count);

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
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(a_translate);
  menu->addAction(a_add_word);
  menu->addAction(a_toggle_direction);
  menu->addSeparator();
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));

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
  toolbar->addAction(standardAction(Cut));
  toolbar->addAction(standardAction(Copy));
  toolbar->addAction(standardAction(Paste));
  toolbar->addSeparator();
  toolbar->addAction(a_translate);
  toolbar->addAction(a_add_word);
  toolbar->addAction(a_toggle_direction);
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::updateStatusBar()
{
  l_sb_word_count_global->setText(_("Word count:") + QLatin1String(" ") +
    QString::number(1000));
  l_sb_combinations_count->setText(_("Dictionary size:") + QLatin1String(" ") +
    QString::number(100));
}

void MainWindow::addWord()
{
  AddWordDialog dialog;

  dialog.m_lineedit_1->setText(m_le_input->text());

  if (dialog.exec()) {

  }
}

void MainWindow::translate()
{
  int connection_id = 0;

  //QSqlDatabase db = QSqlDatabase::database("connection-name");

  if (! m_dictionary_db.isOpen()) {
    qWarning() << "db not open";
    return;
  }

  QSqlQuery query(m_dictionary_db);

  if (! query.prepare("SELECT connection_id FROM words WHERE value = :word")) {
    qWarning() << "prepare failed";
	return;
  }

  query.bindValue(":word", m_le_input->text());

  if (! query.exec()) {
    qWarning() << "exec failed";
	return ;
  }

  if (query.next()) {   // while?
    connection_id = query.value(0).toInt();
  }

  if (connection_id <= 0) {
    qWarning() << "wrong connection id";
    return;
  }

  if (! query.prepare("SELECT value FROM words WHERE connection_id = :connection_id AND "
                                                    "locale_id     = :locale_id")) {
    qWarning() << "prepare failed";
	return;
  }

  query.bindValue(":connection_id", connection_id);
  query.bindValue(":locale_id",     2);
  
  if (! query.exec()) {
    qWarning() << "exec failed";
	return;
  }

  QString s = "";

  while (query.next()) {
    s += query.value(0).toString() + " ";
  }

  m_te_output->setPlainText(s);
}

void MainWindow::toggleDirection()
{
  int i = m_cb_input_language->currentIndex();
  int o = m_cb_output_language->currentIndex();

  m_cb_input_language->setCurrentIndex(o);
  m_cb_output_language->setCurrentIndex(i);

  QString s = m_le_input->text();
  m_le_input->setText(m_te_output->toPlainText());
  m_te_output->setPlainText(s);

  translate();
}

void MainWindow::loadSupportedLanguages()
{
  QSqlDatabase iso_codes_db = QSqlDatabase::addDatabase("QSQLITE", "iso_codes_db");
  QString filename = dynamic_cast<OEG::Qt::Application *>(qApp)->locateFile("iso-codes.db",
                                                                       OEG::Qt::Application::Database);
  iso_codes_db.setDatabaseName(QDir::toNativeSeparators(filename));

  if (! iso_codes_db.open()) {
    qWarning() << "database not open:";
	QSqlError le = iso_codes_db.lastError();
	qWarning() << le.text();
    return;
  }

  if (! iso_codes_db.isOpen()) {
    qWarning() << "db not open";
    return;
  }

  QSqlQuery query(iso_codes_db);

  if (! query.exec("SELECT languages.value FROM languages INNER JOIN locales "
                                               "ON locales.language_id = languages.id")) {
    qWarning() << "exec failed";
	return;
  }

  m_supported_languages << _("?");
  m_supported_languages << _("*");

  while (query.next()) {
    m_supported_languages << query.value(0).toString();
  }

  iso_codes_db.close();
}

void MainWindow::currentIndexChangedInputCombobox(const QString &text)
{
}

void MainWindow::currentIndexChangedOutputCombobox(const QString &text)
{
}

