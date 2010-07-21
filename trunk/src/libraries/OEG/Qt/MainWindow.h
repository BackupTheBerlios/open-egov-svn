// $Id$

#pragma once

#include <OEG/Common.h>

#include <QMainWindow>
#include <QList>
#include <QString>

class QAction;

namespace OEG { namespace Qt {

class ToolProvider;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  enum StandardAction {
    AboutApp,
    AboutQt,
    Close,
    Copy,
    Cut,
    Delete,
    Exit,
    HelpContents,
    HelpIndex,
    HelpSearch,
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
    Save,
    SaveAs,
    SelectAll,
    Undo
  };

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~MainWindow();

    QAction *standardAction(const QString &baseName);
    QAction *standardAction(const StandardAction &action);

  protected:
    void createAll();

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createStatusBar();
    virtual void createToolBars();
    virtual void createToolProvider();

    QAction *addStandardAction(const QString &baseName, const QString &title,
                               const QString &info, const QString &keySequence = QString());

  private:
    QString standardActionName(const StandardAction &action);

  protected:
    ToolProvider      *m_tool_provider;
    QList<QAction *>   m_actions;
};

}}

