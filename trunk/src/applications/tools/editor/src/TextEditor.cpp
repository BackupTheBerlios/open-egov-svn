// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
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

#include <OEG/Qt/Application.h>

#include <QAction>
#include <QColor>
#include <QContextMenuEvent>
#include <QFontMetrics>
#include <QIcon>
#include <QMenu>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextLayout>

#include "TextEditor.h"

TextEditor::TextEditor(QWidget *parent /*=0*/)
 : QTextEdit(parent)
{
  m_right_margin_show            = true;
  m_right_margin_position        = 80;
  m_right_margin_color           = QColor(180, 180, 255);
  m_right_margin_area_show       = true;
  m_right_margin_area_color      = QColor(240, 240, 240);
  m_line_numbers_show            = false;
  m_line_numbers_width           = 40;
  m_line_numbers_bg_color        = QColor(255, 250, 205);
  m_line_numbers_fg_color        = QColor(  0, 200, 100);
  m_highlight_current_line_left  = false;
  m_highlight_current_line_right = false;
  m_highlight_current_line_color = Qt::yellow;
  m_warning_text                 = "!!! Warning Warning Warning !!!";

  setLineWrapMode(QTextEdit::NoWrap);
  setUndoRedoEnabled(true);
  setViewportMargins(0, 0, 0, 0);

  connect(this,                         SIGNAL(cursorPositionChanged()),
          this,                         SLOT(cursorPositionChangedSlot()));
  connect(verticalScrollBar(),          SIGNAL(valueChanged(int)),
          this,                         SLOT(update()));
  connect(this,                         SIGNAL(textChanged()),
          this,                         SLOT(update()));
  //connect(document()->documentLayout(), SIGNAL(update(QRectF &)),
  //        this,                         SLOT(update()));
  connect(document(),                   SIGNAL(modificationChanged(bool)),
          this,                         SIGNAL(contentModified(bool)));
}

void TextEditor::documentLayoutUpdateSlot(const QRectF &rect)
{
  update();
}

TextEditor::~TextEditor()
{
}

void TextEditor::showLineNumbers(const bool show /*=true*/)
{
  if (show == m_line_numbers_show)
    return;

  m_line_numbers_show = show;

  if (show) {
    if (m_line_numbers_width < 1)
      m_line_numbers_width = 50;

    setViewportMargins(m_line_numbers_width, 0, 0, 0);
  }
  else {
    setViewportMargins(0, 0, 0, 0);
  }

  repaint();
}

void TextEditor::setLineNumbersWidth(const int width)
{
  if (m_line_numbers_width == width)
    return;

  m_line_numbers_width = width;

  // If the space is not enough, it is expanded depending on the line count of the text.

#if 0
  const QFontMetrics fm(font());
  int maxWidth = fm.width(QString::number(lines())) + 2 * 2 + 1;

  if (maxWidth > m_line_numbers_width)
    m_line_numbers_width = maxWidth;
#endif

  repaint();
}

void TextEditor::highlightCurrentLineRight(const bool highlight /*=true*/)
{
  if (m_highlight_current_line_right == highlight)
    return;

  m_highlight_current_line_right = highlight;

  repaint();
}

void TextEditor::highlightCurrentLineLeft(const bool highlight /*=true*/)
{
  if (m_highlight_current_line_left == highlight)
    return;

  m_highlight_current_line_left = highlight;

  repaint();
}

void TextEditor::highlightCurrentLine(const bool highlight /*=true*/)
{
  highlightCurrentLineRight(highlight);
  highlightCurrentLineLeft(highlight);
}

void TextEditor::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu *menu = createStandardContextMenu();
  menu->addAction(_("Test"));
  menu->exec(event->globalPos());
  delete menu;
}

void TextEditor::paintEvent(QPaintEvent *event)
{
  paintRightMargin();
  paintCurrentLine();
  paintWarningText();

  QTextEdit::paintEvent(event);
}

bool TextEditor::event(QEvent *event) 
{
  if (event->type() == QEvent::Paint) 
  {
    paintLineNumbers();
  }

  return QTextEdit::event(event);
}

void TextEditor::paintLineNumbers()
{
  if (! m_line_numbers_show || (m_line_numbers_width < 1))
    return;

  QPainter painter(this);                                  // Called from event(), draw into the free margin area.

  painter.fillRect(0, 0, m_line_numbers_width, height(), m_line_numbers_bg_color);       // Fill background.

  if (m_highlight_current_line_left) {
    painter.fillRect(0, cursorRect().y(),                  // Fill the background of the line number of the current line.
                     m_line_numbers_width, cursorRect().height(), m_highlight_current_line_color);
  }

  // Between line number area and text area is a 1px gray line. It can be changed to another color: TODO
  painter.fillRect(m_line_numbers_width, 0, 1, height(), QColor(200, 200, 200));

  int verticalScrollBarValue = verticalScrollBar()->value();
  int lineNumber = 1;
  int currentLine = textCursor().blockNumber() + 1;

  qDebug() << "CL" << currentLine << "BC" << document()->blockCount() << "LB" << document()->lastBlock().blockNumber()
           << "LC(LB)" << document()->lastBlock().lineCount();

  for (QTextBlock block = document()->begin(); block.isValid(); block = block.next(), lineNumber++) {
    QTextLayout *layout = block.layout();
    QPointF position = layout->position();

    if (position.y() + layout->boundingRect().height() < verticalScrollBarValue)
      continue;
    if (position.y() > verticalScrollBarValue + viewport()->height())
      break;

    QString s = QString::number(lineNumber);
    painter.drawText(m_line_numbers_width - fontMetrics().width(s) - 3,
                     position.y() - verticalScrollBarValue + fontMetrics().ascent() + 1, s);
  }
}

void TextEditor::paintCurrentLine()
{
  if (! m_highlight_current_line_right)
    return;

  QPainter painter(viewport());

  QRect rect = cursorRect();                               // Only the cursor area as rect.
  rect.setX(0);                                            // Expand the rect from left ...
  rect.setWidth(viewport()->width());                      // ... to right.

  painter.fillRect(rect, QBrush(m_highlight_current_line_color));
}

void TextEditor::paintRightMargin()
{
  QPainter painter(viewport());

  int x = m_right_margin_position * fontMetrics().width("8");

  if (m_right_margin_area_show) {
    painter.fillRect(x+1, 0, width()-(x+1), height(), m_right_margin_area_color);
  }

  if (m_right_margin_show) {
    QLine line = QLine(x, 0, x, viewport()->height());

    painter.setPen(Qt::DotLine);
    painter.setPen(m_right_margin_color);
    painter.drawLine(line);
  }

  painter.end();
}

void TextEditor::setWarningText(const QString &text)
{
  if (m_warning_text == text)
    return;

  m_warning_text = text;

  update();
}

void TextEditor::paintWarningText()
{
  if (m_warning_text.length() < 1)
    return;

  QPainter painter(viewport());

  painter.setPen(Qt::red);
  painter.setFont(QFont("Arial", 30));
  painter.drawText(viewport()->rect(), Qt::AlignCenter, m_warning_text);
}

void TextEditor::cursorPositionChangedSlot()
{
  viewport()->update();                                    // Update the text area to highlight the correct line.

  if (m_line_numbers_show && m_highlight_current_line_right)    // Update the line numbers area at the left side.
    repaint();
}

