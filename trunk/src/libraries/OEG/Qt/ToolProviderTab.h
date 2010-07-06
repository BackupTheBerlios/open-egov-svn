// $Id$

#pragma once

#include <QColor>
#include <QIcon>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>
#include <QVariantAnimation>
#include <QWidget>

#include <QObject>
#include <QString>

#include <QDebug>

namespace OEG { namespace Qt {

class ToolProviderTab : public QObject
{
  public:
    ToolProviderTab(QObject *parent = 0);
    ~ToolProviderTab();

    QString text;
    QString toolTip;
    QString whatsThis;
    QColor  selectedTextColor;
    QColor  selectedBackgroundColor;
    QColor  textColor;
    QColor  backgroundColor;

  protected:
    

  private:


  protected:

};

}}

