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

#pragma once

#include <OEG/Qt/MainWindow.h>

#include <QString>
#include <QWidget>
#include <QList>

class QTableWidget;
class QProcess;
class QLabel;
class QLineEdit;

class OEG::Qt::TabbedMenuBar;

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
    virtual void createTabbedMenuBar() {};

    void processInit();

  protected slots:
    void updatePackageList();
    void clearEnvironment();
    void installRequiredPackages();
    void compilePackage();
    void createBinaryArchive();
    void newPackage();
    void editPackage();
    void overlayPackage();
    void openCommandLineInterface();
    void commonSettings();
    void onTableCustomContextMenuRequested(const QPoint &pos);
    void updateStatusBar();

    void processReadStdOut();                              // Worker process related slots.
    void processStarted();
    void processFinished(int signal);

    void filterTextChanged(const QString &text);           // Text in filter line edit in toolbar changed.

  protected:
    QTableWidget *m_table_widget;
    QProcess     *m_background_process;                    // Help process e.g. to scan the instructions files.
    QProcess     *m_worker_process;                        // The building and installing process. Opens a bash.
    QLabel       *m_number_of_packages;
    QLabel       *m_number_of_selected_rows;
    QLineEdit    *m_package_filter;
};

