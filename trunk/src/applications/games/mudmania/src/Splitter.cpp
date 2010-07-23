// $Id$

#include <OEG/Common.h>

#include <QApplication>
#include <QLatin1String>

#include "Splitter.h"
#include "SplitterHandle.h"

Splitter::Splitter(QWidget *parent /*=0*/)
 : QSplitter(parent)
{
}

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent /*=0*/)
 : QSplitter(orientation, parent)
{
}

QSplitterHandle *Splitter::createHandle()
{
  return new SplitterHandle(orientation(), this);
}

