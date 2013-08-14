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

#pragma once

#include <QColor>
#include <QFont>
#include <QString>
#include <QTextEdit>
#include <QWidget>

class QContextMenuEvent;
class QPaintEvent;
class QEvent;

class TextEditor : public QTextEdit
{
  Q_OBJECT

  public:
    TextEditor(QWidget *parent = 0);
    virtual ~TextEditor();

    void showLineNumbers(const bool show = true);
    void setLineNumbersWidth(const int width);
    void highlightCurrentLine(const bool highlight = true);
    void highlightCurrentLineLeft(const bool highlight = true);
    void highlightCurrentLineRight(const bool highlight = true);
    void setWarningText(const QString &text);

    unsigned long int lineCount();

  protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual bool event(QEvent *event);
    void updateLineNumbersViewPort();

  public slots:
    void cursorPositionChangedSlot();
    void documentLayoutUpdateSlot(const QRectF &rect);

  signals:
    void lineCountChanged();

  private:
    void paintLineNumbers();
    void paintCurrentLine();
    void paintRightMargin();
    void paintWarningText();

  protected:
    bool     m_right_margin_show;                          // 
    int      m_right_margin_position;                      // 
    QColor   m_right_margin_color;                         // 
    bool     m_right_margin_area_show;                     // 
    QColor   m_right_margin_area_color;                    // 
    bool     m_line_numbers_show;                          // Show column with line numbers left of the content.
    int      m_line_numbers_width;                         // The width of the line numbers column.
    QColor   m_line_numbers_fg_color;                      // 
    QColor   m_line_numbers_bg_color;                      // 
    bool     m_highlight_current_line_left;                // Enable the highlighting of the current line.
    bool     m_highlight_current_line_right;               // Enable the highlighting of the current line.
    QColor   m_highlight_current_line_color;               // Color for highlighting the current line.
    QString  m_warning_text;
    bool     m_warning_text_show;
    int      m_warning_text_hide_after_x_secs;
    QColor   m_warning_text_color;
    QFont    m_warning_text_font;
    int      m_warning_text_position_x;
    int      m_warning_text_position_y;
    bool     m_warning_text_position_use;

    bool              m_dynamic_line_numbers_width;
    unsigned long int m_line_count;                        // Needed to ensure that LC area's width is big enough.
    bool              m_text_changed;
};

