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

#include <OEG/Common.h>

#include <QMainWindow>
#include <QList>
#include <QString>

class QAction;
class QLayout;
class QPrinter;

namespace OEG { namespace Qt {

class ToolProvider;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    enum StandardAction {
      AboutApp,
      AboutQt,
      //Add: see "New".
      Clear,
      ConnectToggle,
      Close,
      Copy,
      Cut,
      Delete,
      Edit,
      Exit,
      GoToHomepage,
      HelpContents,
      HelpIndex,
      HelpSearch,
      HelpForum,
      //Load: see "Open".
      New,
      Open,
      Paste,
      Plugins,
      Preferences,
      PreferencesColors,
      PreferencesCommon,
      PreferencesFonts,
      PreferencesShortcuts,
      Print,
      PrintPreview,
      PrintSettings,
      //Quit: see "Exit".
      Redo,
      Reload,
      ReportBug,
      Save,
      SaveAs,
      SelectAll,
      Undo,
      ZoomFitWidth,
      ZoomFitWindow,
      ZoomIn,
      ZoomOut,
      ZoomNormal
    };

    enum DataStorageMode {
      DoNothing,
      XmlFile,
      Database
    };

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    QAction *standardAction(const StandardAction &action);
    QString applicationBaseName() const;

  public slots:
    void standardActionAboutApp();
    void standardActionClear();
    void standardActionClose();
    void standardActionCopy();
    void standardActionCut();
    void standardActionConnectToggle();
    void standardActionDelete();
    void standardActionEdit();
    void standardActionHelpContents();
    void standardActionHelpIndex();
    void standardActionHelpSearch();
    void standardActionOpen();
    void standardActionNew();
    void standardActionPaste();
    void standardActionPreferences();
    void standardActionPrint();
    void standardActionPrintPreview();
    void standardActionPrintSettings();
    void standardActionRedo();
    void standardActionReload();
    void standardActionReportBug();
    void standardActionSave();
    void standardActionSaveAs();
    void standardActionUndo();
    void standardActionZoomFitWidth();
    void standardActionZoomFitWindow();
    void standardActionZoomIn();
    void standardActionZoomOut();
    void standardActionZoomNormal();

  protected:
    virtual void createAll();

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createStatusBar();
    virtual void createToolBars();
    virtual void createToolProvider();

    QAction *addStandardAction(const QString &baseName, const QString &title,
                               const QString &info, const QString &keySequence = QString());
    void addHelpMenu();

    void setDefaultWindowSize(unsigned int width, unsigned int height);
    void setCentralLayout(QLayout *layout);

  private:
    QAction *createStandardAction(const StandardAction &action, const QString &baseName);
    QAction *findStandardAction(const QString &baseName);         // TODO: avoid string search, store enum value.
    QString standardActionName(const StandardAction &action);

  protected:
    ToolProvider      *m_tool_provider;
    QList<QAction *>   m_actions;
    unsigned int       m_default_width;
    unsigned int       m_default_height;
    QPrinter          *m_printer;
    bool               m_printer_initialized;
    DataStorageMode    m_data_storage_mode;
};

}}

