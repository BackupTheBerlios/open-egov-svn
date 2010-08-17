// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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
      Clear,
      ConnectToggle,
      Close,
      Copy,
      Cut,
      Delete,
      Exit,
      GoToHomepage,
      HelpContents,
      HelpIndex,
      HelpSearch,
      HelpForum,
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

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    QAction *standardAction(const StandardAction &action);

  public slots:
    void standardActionAboutApp();
    void standardActionConnectToggle();
    void standardActionHelpContents();
    void standardActionHelpIndex();
    void standardActionHelpSearch();

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
};

}}

