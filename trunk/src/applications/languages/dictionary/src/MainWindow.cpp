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
#include "Language.h"
#include "WordType.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  m_language_id_input  = 0;  // TODO: store values from last session.
  m_language_id_output = 0;

  setWindowIcon(QIcon("icon.png"));

  loadSupportedLanguages();

  m_le_input  = new QLineEdit(this);
  m_te_output = new QTextEdit(this);
  m_te_output->setReadOnly(true);
  m_cb_input_language = new QComboBox(this);
  m_cb_input_language->setDuplicatesEnabled(false);
  m_cb_input_language->setEditable(false);
  m_cb_input_language->addItems(supportedLanguages(true, true));
  m_cb_input_language->setCurrentIndex(0);
  m_cb_output_language = new QComboBox(this);
  m_cb_output_language->setDuplicatesEnabled(false);
  m_cb_output_language->setEditable(false);
  m_cb_output_language->addItems(supportedLanguages(false, true));
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
    qWarning() << "Database not open:" << m_dictionary_db.lastError().text();
    qWarning() << "File:" << dbfile;
  }

  loadWordTypes();
}

MainWindow::~MainWindow()
{
  while (! m_languages.isEmpty())
    delete m_languages.takeFirst();

  while (! m_word_types.isEmpty())
    delete m_word_types.takeFirst();
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
  menu->addSeparator();
  menu->addAction(standardAction(Delete));

  menu = getStandardMenu(SettingsMenu);
  action = menu->addAction(_("Common..."));
  connect(action, SIGNAL(triggered()),
          this,   SLOT(commonSettings()));

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
  int index;
  AddWordDialog dialog;

  dialog.m_cb_1_language->setDuplicatesEnabled(false);
  dialog.m_cb_1_language->setEditable(false);
  dialog.m_cb_1_language->addItems(supportedLanguages(false, false));

  index = dialog.m_cb_1_language->findText(m_cb_input_language->currentText(), Qt::MatchExactly | Qt::MatchCaseSensitive);
  dialog.m_cb_1_language->setCurrentIndex(index);

  dialog.m_cb_2_language->setDuplicatesEnabled(false);
  dialog.m_cb_2_language->setEditable(false);
  dialog.m_cb_2_language->addItems(supportedLanguages(false, false));

  index = dialog.m_cb_2_language->findText(m_cb_output_language->currentText(), Qt::MatchExactly | Qt::MatchCaseSensitive);
  dialog.m_cb_2_language->setCurrentIndex(index);

  dialog.m_cb_1_word_type->setDuplicatesEnabled(false);
  dialog.m_cb_1_word_type->setEditable(false);
  dialog.m_cb_1_word_type->addItems(m_supported_word_types);
  dialog.m_cb_1_word_type->setCurrentIndex(-1);

  dialog.m_cb_2_word_type->setDuplicatesEnabled(false);
  dialog.m_cb_2_word_type->setEditable(false);
  dialog.m_cb_2_word_type->addItems(m_supported_word_types);
  dialog.m_cb_2_word_type->setCurrentIndex(-1);

  dialog.m_lineedit_1->setText(m_le_input->text());

  if (! dialog.exec())
    return;

  qDebug() << "Adding:" << dialog.m_lineedit_1->text() << dialog.m_lineedit_2->text();

  QSqlDatabase db = QSqlDatabase::database("dictionary_db");

  if (! db.isOpen()) {
    qWarning() << "Database not open.";
    return;
  }

  QSqlQuery query(db);

#if 0
  if (! query.prepare("INSERT INTO words(id,language_id,word_type_id,connection_id,value) "
                      "VALUES "
                      ":language_id")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":language_id",   152 /*de*/);
  
  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return;
  }

  while (query.next()) {
    WordType *type = new WordType(this);
    type->m_id    = query.value(0).toInt();
    type->m_value = query.value(1).toString();
    m_word_types << type;

    m_supported_word_types << query.value(1).toString();
  }
#endif
}

void MainWindow::translate()
{
  int connection_id = 0;

  if (! m_dictionary_db.isOpen()) {
    qWarning() << "db not open";
    return;
  }

  QSqlQuery query(m_dictionary_db);

  if (! query.prepare("SELECT connection_id FROM words WHERE value = :word AND "
                                                    "language_id   = :language_id")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":word",        m_le_input->text());
  query.bindValue(":language_id", m_language_id_input);

  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return ;
  }

  if (query.next()) {   // while?
    connection_id = query.value(0).toInt();
  }

  if (connection_id <= 0) {
    qWarning() << "Wrong connection id.";
    return;
  }

  if (! query.prepare("SELECT value FROM words WHERE connection_id = :connection_id AND "
                                                    "language_id   = :language_id")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":connection_id", connection_id);
  query.bindValue(":language_id",   m_language_id_output);
  
  if (! query.exec()) {
    qWarning() << "exec() failed.";
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

QStringList MainWindow::supportedLanguages(const bool detectLanguage /*=false*/, const bool allLanguages /*=false*/)
{
  QStringList list;

  if (detectLanguage) {
    list << _("?");
  }

  if (allLanguages) {
    list << _("*");
  }

  list += m_supported_languages;

  return list;
}

void MainWindow::loadSupportedLanguages()
{
  QSqlDatabase iso_codes_db = QSqlDatabase::addDatabase("QSQLITE", "iso_codes_db");
  QString filename = dynamic_cast<OEG::Qt::Application *>(qApp)->locateFile("iso-codes.db",
                                                                       OEG::Qt::Application::Database);
  iso_codes_db.setDatabaseName(QDir::toNativeSeparators(filename));

  if (! iso_codes_db.open()) {
    qWarning() << "Could not open database:";
    QSqlError le = iso_codes_db.lastError();
    qWarning() << le.text();
    return;
  }

  if (! iso_codes_db.isOpen()) {
    qWarning() << "Database is not open.";
    return;
  }

  QSqlQuery query(iso_codes_db);

  // The locales table is deprecated now, will move to ISO 639-3 and additional meta data (favorites).
  // Currently we use an additional column "dictionary" to select the wanted relevant dictionaries.

  if (! query.exec("SELECT id,value,alpha2code,alpha3codeb,translation_id FROM languages WHERE dictionary = 1")) {
    qWarning() << "exec() failed.";
    return;
  }

  while (query.next()) {
    Language *lang = new Language(this);
    lang->m_id             = query.value(0).toInt();
    lang->m_value          = query.value(1).toString();
    lang->m_alpha2code     = query.value(2).toString();
    lang->m_alpha3codeb    = query.value(3).toString();
    lang->m_alpha3codet    = query.value(4).toString();
    lang->m_translation_id = query.value(5).toInt();
    m_languages << lang;

    m_supported_languages << query.value(1).toString();
  }

  iso_codes_db.close();
}

void MainWindow::loadWordTypes()
{
  QSqlDatabase db = QSqlDatabase::database("dictionary_db");

  if (! db.isOpen()) {
    qWarning() << "Database not open.";
    return;
  }

  QSqlQuery query(db);

  if (! query.prepare("SELECT word_types.id,translations.value "
                      "FROM word_types INNER JOIN translations ON translations.id = word_types.id "
                      "WHERE translations.language_id = :language_id")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":language_id",   152 /*de*/);
  
  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return;
  }

  while (query.next()) {
    WordType *type = new WordType(this);
    type->m_id    = query.value(0).toInt();
    type->m_value = query.value(1).toString();
    m_word_types << type;

    m_supported_word_types << query.value(1).toString();
  }
}

void MainWindow::currentIndexChangedInputCombobox(const QString &text)
{
  for (int i = 0; i < m_languages.size(); i++) {
    Language *lang = m_languages.at(i);
    if (lang->m_value == text) {
      m_language_id_input = lang->m_id;
      return;
    }
  }

  if (text == _("?")) {
    m_language_id_input = -1;
    return;
  }

  if (text == _("*")) {
    m_language_id_input = 0;
    return;
  }

  qWarning() << "Unknown language selected:" << text;
}

void MainWindow::currentIndexChangedOutputCombobox(const QString &text)
{
  for (int i = 0; i < m_languages.size(); i++) {
    Language *lang = m_languages.at(i);
    if (lang->m_value == text) {
      m_language_id_output = lang->m_id;
      return;
    }
  }

  if (text == _("*")) {
    m_language_id_output = 0;
    return;
  }

  qWarning() << "Unknown language selected:" << text;
}

