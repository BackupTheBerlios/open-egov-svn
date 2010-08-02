// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/TabWidget.h>

#include <QString.h>
#include <QWidget.h>
#include <QList.h>

class Splitter;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  //Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWidgets();

    void setTitle(const QString &title);
    QString title() const;

  protected:
    OEG::Qt::TabWidget *m_tabs;
    QString             m_title;
    Splitter           *m_splitter;
};

