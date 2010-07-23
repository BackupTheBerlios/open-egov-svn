// $Id$

#pragma once

#include <OEG/Common.h>

#include <QSplitter>
#include <QSplitterHandle>

class SplitterHandle : public QSplitterHandle
{
  Q_OBJECT

  public:
    SplitterHandle(Qt::Orientation orientation, QSplitter *parent);

  protected:
    virtual void paintEvent(QPaintEvent *event);
};

