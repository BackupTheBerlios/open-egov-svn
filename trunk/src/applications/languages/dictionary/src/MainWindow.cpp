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
  // TODO: store settings from last session.

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
  menu->addAction(standardAction(Print));
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
  long l;

  l = numberOfWords(AllWordsInDatabase);
  l_sb_word_count_global->setText(_("Word count:") + QLatin1String(" ") +
    QString::number(l));

  l = numberOfWords(CombinationAB);
  l_sb_combinations_count->setText(_("Dictionary size:") + QLatin1String(" ") +
    QString::number(l));
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

  // Retrieve all needed data.

  int connection_id = maxConnectionId() + 1;
  int language_id_a = languageId(dialog.m_cb_1_language->currentText());
  int language_id_b = languageId(dialog.m_cb_2_language->currentText());
  QString text_a = dialog.m_lineedit_1->text().trimmed();
  QString text_b = dialog.m_lineedit_2->text().trimmed();
  int word_type_id_a = wordTypeId(dialog.m_cb_1_word_type->currentText());
  int word_type_id_b = wordTypeId(dialog.m_cb_2_word_type->currentText());

  qDebug() << "Adding:" << text_a << text_b;
  qDebug() << "  LID a" << language_id_a << "LID b" << language_id_b << "CoID" << connection_id;
  qDebug() << "  WTID a" << word_type_id_a << "WTID b" << word_type_id_b;

  QSqlDatabase db = QSqlDatabase::database("dictionary_db");

  if (! db.isOpen()) {
    qWarning() << "Database not open.";
    return;
  }




  QSqlQuery query(db);

#if 0
  if (! query.prepare("INSERT INTO words(id,language_id,word_type_id,connection_id,value) "
                      "VALUES (NULL,:language_id,:word_type_id,:connection_id,:value)")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":language_id",   language_id_a);
  query.bindValue(":word_type_id",  word_type_id_a);
  query.bindValue(":connection_id", connection_id);
  query.bindValue(":value",         text_a);

  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return;
  }

  if (query.next()) {
    qDebug() << query.value(0).toString();
  }
#endif
}

void MainWindow::translate()
{
  QString result = "";

  int connection_id = 0;

  if (! m_dictionary_db.isOpen()) {
    qWarning() << "Database not open.";
    return;
  }

  QList<int> connection_ids;

  {
    QSqlQuery query(m_dictionary_db);

    int language_id_a = currentLanguageIdA();
    if (language_id_a == 0) {                              // Search all languages for this text phrase.
      if (! query.prepare("SELECT connection_id FROM words WHERE value = :word ORDER BY language_id")) {
        qWarning() << "prepare() failed.";
        return;
      }
    }
    else {                                                 // Search only within the selected language.
      if (! query.prepare("SELECT connection_id FROM words WHERE value = :word "
                          "AND language_id = :language_id ORDER BY language_id")) {
        qWarning() << "prepare() failed.";
        return;
      }

      query.bindValue(":language_id", language_id_a);
    }
    query.bindValue(":word", m_le_input->text().trimmed());

    if (! query.exec()) {
      qWarning() << "exec() failed.";
      return ;
    }

    while (query.next()) {                                 // There may be more than one entries for the search term.
      connection_id = query.value(0).toInt();

      if (connection_id <= 0) {
        qWarning() << "Wrong connection id:" << connection_id;
        break;
      }

      connection_ids << connection_id;
    }
  }

  if (connection_ids.size() <= 0) {
    result = "<strong>" + QLatin1String(_("Text not found.")) + "</strong>";
    m_te_output->setHtml(result);
    return;
  }

  result = "";

  while (! connection_ids.isEmpty()) {
    connection_id = connection_ids.takeFirst();

    QSqlQuery query(m_dictionary_db);

    int language_id_b = currentLanguageIdB();
    if (language_id_b == 0) {                              // Show results for all languages.
      if (! query.prepare("SELECT value,word_type_id "
                          "FROM words WHERE connection_id = :connection_id "
                                           "ORDER BY language_id")) {
        qWarning() << "prepare() failed.";
        return;
      }
    }
    else {
      if (! query.prepare("SELECT value,word_type_id "
                          "FROM words WHERE connection_id = :connection_id AND "
                                           "language_id   = :language_id")) {
        qWarning() << "prepare() failed.";
        return;
      }

      query.bindValue(":language_id", language_id_b);
    }
    query.bindValue(":connection_id", connection_id);

    if (! query.exec()) {
      qWarning() << "exec() failed.";
      return;
    }

    // TODO: Add number.

    while (query.next()) {
      result += "<strong>" + query.value(0).toString() + "</strong>";
      int word_type = query.value(1).toInt();
      result += " (" + wordTypeValue(word_type) + ")<br><br>";
    }
  }

  if (result.length() == 0)
    result = "<strong>" + QLatin1String(_("No results found in dictionary.")) + "</strong>";

  m_te_output->setHtml(result);
}

void MainWindow::toggleDirection()
{
  QString text;
  int     index;

  text  = m_cb_output_language->currentText();
  index = m_cb_input_language->findText(text, Qt::MatchExactly | Qt::MatchCaseSensitive);
  text  = m_cb_input_language->currentText();
  m_cb_input_language->setCurrentIndex(index);
  index = m_cb_output_language->findText(text, Qt::MatchExactly | Qt::MatchCaseSensitive);
  m_cb_output_language->setCurrentIndex(index);

  text = m_le_input->text();
  m_le_input->setText(m_te_output->toPlainText());
  m_te_output->setPlainText(text);

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
                      "FROM word_types INNER JOIN translations ON translations.id = word_types.translation_id "
                      "WHERE translations.language_id = :language_id")) {
    qWarning() << "prepare() failed.";
    return;
  }

  query.bindValue(":language_id", 152 /*de*/);     // TODO: Use GUI language.
  
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
  updateStatusBar();

  qWarning() << "Input language selected:" << text;
}

void MainWindow::currentIndexChangedOutputCombobox(const QString &text)
{
  updateStatusBar();

  qWarning() << "Output language selected:" << text;
}

int MainWindow::maxConnectionId()
{
  QSqlDatabase db = QSqlDatabase::database("dictionary_db");

  if (! db.isOpen()) {
    qWarning() << "Database not open.";
    return -1;
  }

  QSqlQuery query("SELECT max(connection_id) FROM words", db);

  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return -2;
  }

  if (query.next()) {
    int id = query.value(0).toInt();
    qDebug() << "Max connection_id:" << id;
    return id;
  }

  return 0;
}

QString MainWindow::wordTypeValue(const int id)
{
  for (int i = 0; i < m_word_types.size(); i++) {
    WordType *type = m_word_types.at(i);
    if (type->m_id == id) {
      return type->m_value;
    }
  }

  return "";
}

int MainWindow::wordTypeId(const QString &value)
{
  for (int i = 0; i < m_word_types.size(); i++) {
    WordType *type = m_word_types.at(i);
    if (type->m_value == value) {
      return type->m_id;
    }
  }

  return 0;
}

// Finds for a language name the language id using the m_languages list.
// Needed to find the ID for the SQL query by reading the combobox popup values.

int MainWindow::languageId(const QString &languageName)
{
  for (int i = 0; i < m_languages.size(); i++) {
    Language *lang = m_languages.at(i);
    if (lang->m_value == languageName) {
      return lang->m_id;
    }
  }

  return 0;
}

int MainWindow::currentLanguageIdA()
{
  QString text = m_cb_input_language->currentText();

  if (text == _("?"))
    return -1;

  if (text == _("*"))
    return 0;

  return languageId(text);
}

int MainWindow::currentLanguageIdB()
{
  QString text = m_cb_output_language->currentText();

  if (text == _("*"))
    return 0;

  return languageId(text);
}

unsigned long MainWindow::numberOfWords(NumberOfWords which)
{
  QSqlDatabase db = QSqlDatabase::database("dictionary_db");

  if (! db.isOpen()) {
    qWarning() << "Database not open.";
    return -1;
  }

  QString sql;
  switch (which) {
    case AllWordsInDatabase:
      sql = "SELECT count(*) FROM words";
      break;
    case OnlyLanguageA:
      sql = "SELECT count(*) FROM words WHERE language_id=:l_id_a";
      break;
    case OnlyLanguageB:
      sql = "SELECT count(*) FROM words WHERE language_id=:l_id_b";
      break;
    case CombinationAB:
      sql = "SELECT DISTINCT count(id) "
            "FROM words "
            "WHERE language_id = :l_id_a AND connection_id IN "
            "( "
            "  SELECT connection_id "
            "  FROM words "
            "  WHERE language_id = :l_id_b "
            ")";
      break;
    default:
      break;
  }

  QSqlQuery query(db);

  if (! query.prepare(sql)) {
    qWarning() << "prepare() failed.";
    return 0L;
  }

  if ((which == OnlyLanguageA) || (which == CombinationAB))
    query.bindValue(":l_id_a", currentLanguageIdA());
  if ((which == OnlyLanguageB) || (which == CombinationAB))
    query.bindValue(":l_id_b", currentLanguageIdB());

  if (! query.exec()) {
    qWarning() << "exec() failed.";
    return 0L;
  }

  if (query.next()) {
    int id = query.value(0).toInt();
    qDebug() << "max connection_id:" << id;
    return id;
  }

  return 0L;
}

