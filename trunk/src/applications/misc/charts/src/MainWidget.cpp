// $Id$

#include <QWidget.h>

#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent /*=0*/, const char *name /*=0*/)
 : QTextEdit(parent, name)
{
}

void MainWidget::setTitle(const QString &title)
{
  m_title = title;
}

QString MainWidget::title() const
{
  return m_title;
}

