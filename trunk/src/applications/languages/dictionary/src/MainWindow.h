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

#pragma once

#include <OEG/Qt/MainWindow.h>

#include <QString>
#include <QWidget>
#include <QList>
#include <QStringList>
#include <QSqlDatabase>

class QComboBox;
class QLabel;
class QLineEdit;
class QTextEdit;
class QGridLayout;
class QAction;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

    virtual void createActions();
    virtual void createStatusBar();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createTabbedMenuBar();

  protected slots:
    void updateStatusBar();

    void addWord();
    void translate();
    void toggleDirection();

    void currentIndexChangedInputCombobox(const QString &text);
    void currentIndexChangedOutputCombobox(const QString &text);

  protected:
    void loadSupportedLanguages();

  protected:
    QLineEdit   *m_le_input;
    QTextEdit   *m_te_output;
    QComboBox   *m_cb_input_language;
    QComboBox   *m_cb_output_language;
    QLabel      *m_la_input;
    QLabel      *m_la_output;
    QGridLayout *m_layout;
    QAction     *a_add_word;
    QAction     *a_translate;
    QAction     *a_toggle_direction;
    QLabel      *l_sb_word_count_global;
    QLabel      *l_sb_combinations_count;
    QSqlDatabase m_dictionary_db;
    QStringList  m_supported_languages;
    int          m_locale_id_input;
    int          m_locale_id_output;
};

