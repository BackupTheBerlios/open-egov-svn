// $Id$

#pragma once

#include <OEG/Common.h>

#include <QColor>
#include <QEvent>
#include <QIcon>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>
#include <QVariantAnimation>
#include <QWidget>

#include <QList>

#include <QDebug>

#include <OEG/Qt/ToolProviderTab.h>

namespace OEG { namespace Qt {

// The ToolProvider class implements a widget which combines the features of
// QMenu and QToolBar without being a Microsoft Ribbon. It looks like an improved QTabBar,
// but it isn't one, because it's nearly impossible to improve the original QTabBar class.
// Needed features: multi-selection, background colors, a bigger tab spacing, ...

class ToolProvider : public QWidget
{
  Q_OBJECT

  public:
    ToolProvider(QWidget *parent = 0, ::Qt::WindowFlags flags = 0);
    ~ToolProvider();

  protected:


  protected:
    QColor                    m_bg_color;                  // Background color.
    bool                      m_alternative_mode;
    QList<ToolProviderTab *>  m_tab_list;
    ToolProviderTab           m_tab_template;
};

}}

