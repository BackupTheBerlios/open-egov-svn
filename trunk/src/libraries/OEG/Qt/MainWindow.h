// $Id$

#pragma once

#include <OEG/Common.h>

#include <QMainWindow>
#include <QList>

class QAction;

namespace OEG { namespace Qt {

class ToolProvider;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  enum StandardActions {
    New,
    Open,
    Close,
    Save,
    SaveAs,
    Reload,
    Print,
    PrintSettings,
    Quit,
    Undo,
    Redo,
    Cut,
    Copy,
    Paste,
    Delete,
    SelectAll,
    Preferences,
    Plugins,
    HelpContents,
    HelpIndex,
    HelpSearch,
    LicenseOEG,
    LicenseQt
  };

  public:
    MainWindow(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~MainWindow();

  protected:
    void createAll();

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createStatusBar();
    virtual void createToolBars();
    virtual void createToolProvider();

    QAction *addStandardAction(const QString &baseName, const QString &title,
                               const QString &info, const QString &keySequence);
    QAction *standardAction(const QString &baseName);

  private:

  protected:
    ToolProvider      *m_tool_provider;
    QList<QAction *>   m_actions;
};

}}

