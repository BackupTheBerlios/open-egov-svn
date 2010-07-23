// $Id$

#pragma once

#include <OEG/Common.h>

#include <QSplitter>
#include <QSplitterHandle>

class Splitter : public QSplitter
{
  Q_OBJECT

  public:
    Splitter(QWidget *parent = 0);
    Splitter(Qt::Orientation orientation, QWidget *parent = 0);

  protected:
    virtual QSplitterHandle *createHandle();
};

