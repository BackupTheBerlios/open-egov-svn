// $Id$
//
// G.A.S.I. Libraries Pack: Qt Extension Library
// Copyright (C) 2005-2008 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <QtGui>

#include "ColorButton.h"

ColorButton::ColorButton(QWidget *parent /*=0*/)
{
  ColorButton(QColor(), parent);
}

ColorButton::ColorButton(const QColor &color, QWidget *parent /*=0*/)
 : QPushButton(parent)
{
  setColor(color);

  connect(this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

ColorButton::~ColorButton()
{
}

QColor ColorButton::color() const
{
  return m_color;
}

void ColorButton::setColor(const QColor &color)
{
  if (m_color != color) {
    m_color = color;

    //setAutoFillBackground(true);

    // Warning: Do not use this function in conjunction with Qt Style Sheets.
    // When using style sheets, the palette of a widget can be customized using
    // the "color", "background-color", "selection-color",
    // "selection-background-color" and "alternate-background-color".

    QPalette pal = palette();

    // Change QPalette::Button, this is used in qDrawShadePanel() called from
    // QCommonStyle::drawPrimitive(PE_PanelButtonCommand, ...). If you want
    // to paint for yourself, use QPalette::Window together with setAutoFillBackground(true);

    pal.setColor(QPalette::Button, m_color);

    setPalette(pal);
    //qApp->setStyleSheet("ColorButton { background-color: blue; }");

    update(); //repaint();

    emit changed(m_color);
  }
}

void ColorButton::chooseColor()
{
  QColor c = QColorDialog::getColor(color(), this);

  if (c.isValid())
    setColor(c);
}

// Analog: QCommonStyle::drawControl(CE_PushButtonBevel, const QStyleOption *opt, QPainter *p, const QWidget *widget)

void ColorButton::paintEvent(QPaintEvent *e)
{
  QStylePainter p(this);
  QStyleOptionButton option;
  initStyleOption(&option);
  p.drawControl(QStyle::CE_PushButton, option);
return;
  //option.initFrom(this);
  option.state = isDown() ? QStyle::State_Sunken : QStyle::State_Raised;

  if (isDefault())
    option.features |= QStyleOptionButton::DefaultButton;

  option.text = text();
  option.icon = icon();

  QPainter painter(this);

  //style()->drawControl(QStyle::CE_PushButtonBevel, &option, &painter, this);
  QRect br = option.rect;
  int dbi = style()->pixelMetric(QStyle::PM_ButtonDefaultIndicator, &option, this);

  //style()->drawPrimitive(QStyle::PE_FrameDefaultButton, &option, &painter, this);
  //style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &option, &painter, this); // rechteck, bevel

  if (option.features & QStyleOptionButton::DefaultButton)
    style()->drawPrimitive(QStyle::PE_FrameDefaultButton, &option, &painter, this);
  if (option.features & QStyleOptionButton::AutoDefaultButton)
    br.setCoords(br.left() + dbi, br.top() + dbi, br.right() - dbi, br.bottom() - dbi);
  if (!(option.features & (QStyleOptionButton::Flat | QStyleOptionButton::CommandLinkButton))
        || option.state & (QStyle::State_Sunken | QStyle::State_On)
        || (option.features & QStyleOptionButton::CommandLinkButton && option.state & QStyle::State_MouseOver)) {
    QStyleOptionButton tmpBtn = option;
    tmpBtn.rect = br;
    style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &tmpBtn, &painter, this);
  }
  if (option.features & QStyleOptionButton::HasMenu) {
    int mbi = style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &option, this);
    QRect ir = option.rect;
    QStyleOptionButton newBtn = option;
    newBtn.rect = QRect(ir.right() - mbi + 2, ir.height()/2 - mbi/2 + 3, mbi - 6, mbi - 6);
    style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &newBtn, &painter, this);
  }

  QStyleOptionButton subopt = option;
  subopt.rect = style()->subElementRect(QStyle::SE_PushButtonContents, &option, this);
  style()->drawControl(QStyle::CE_PushButtonLabel, &subopt, &painter, this);

  if (option.state & QStyle::State_HasFocus) {
    QStyleOptionFocusRect fropt = *qstyleoption_cast<const QStyleOptionFocusRect *>(&option);
    fropt.rect = style()->subElementRect(QStyle::SE_PushButtonFocusRect, &option, this);
    style()->drawPrimitive(QStyle::PE_FrameFocusRect, &fropt, &painter, this);
  }
}

