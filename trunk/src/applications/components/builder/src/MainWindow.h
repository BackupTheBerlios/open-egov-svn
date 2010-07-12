// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>

#include <QString.h>
#include <QWidget.h>
#include <QList.h>

class OEG::Qt::ToolProvider;

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  //Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWindow(QWidget *parent = 0);

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWidgets();

    void setTitle(const QString &title);
    QString title() const;

  protected:
    QString m_title;
};

