// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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
#include <OEG/Qt/TabWidget.h>

#include <QString>
#include <QWidget>
#include <QSqlDatabase>
#include <QStringList>

class QLabel;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  public:
    enum HistoryEntryIDs {
      HEID_FIRST_CONSULT=0,
      HEID_CASE_OPENED,
      HEID_PAID_DUE,
      HEID_SERVED_SUBPOENA,
      HEID_HEARING,
      HEID_REHASHING,
      HEID_CASE_REOPENED,
      HEID_SERVED_PROTOCOL_COPY,
      HEID_WAITING,
      HEID_NOTE,
      HEID_CONSULTATION,
      HEID_REFUNDED_MONEY,
      HEID_CASE_CLOSED,
      HEID_DATABASE_OPENED,
      HEID_CASE_ARCHIVED,
      HEID_CASE_ACCESSED
    };

  public:
    MainWindow(QWidget *parent = 0);

    virtual void createActions();
    virtual void createStatusBar();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createTabbedMenuBar();

  protected:
    void updateStatusBar();

    QStringList catchwordList();
    QStringList resultTypeId();
    QStringList historyEntryId();

    void addHistoryEntry(const int historyEntryId, const QString &value="");

  protected slots:
    void selectForms();
    void selectLaw();

  protected:
    QLabel             *m_sb_file_count;
    QLabel             *m_sb_current_file;
    OEG::Qt::TabWidget *m_tabs;
    QSqlDatabase        m_db;
    int                 m_current_case_id;
};

