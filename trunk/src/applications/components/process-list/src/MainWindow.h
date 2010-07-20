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

    virtual void createActions();
    virtual void createDockWidgets();
    virtual void createMenus();
    virtual void createToolBars();
    virtual void createToolProvider() {};

    void setTitle(const QString &title);
    QString title() const;

  protected:
    QString m_title;
};

