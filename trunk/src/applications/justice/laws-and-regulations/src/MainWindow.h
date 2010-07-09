// $Id$

#pragma once

#include <OEG/Qt/MainWindow.h>

#include <QString.h>
#include <QWidget.h>

class MainWindow : public OEG::Qt::MainWindow
{
  Q_OBJECT

  //Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWindow(QWidget *parent = 0);

    void setTitle(const QString &title);
    QString title() const;

  protected:
    QString m_title;
};

