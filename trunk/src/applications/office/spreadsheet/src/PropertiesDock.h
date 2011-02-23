// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <OEG/Qt/Application.h>

#include <QDockWidget>

class QTableWidget;
class QTableWidgetItem;

class PropertiesDock : public QDockWidget
{
  Q_OBJECT

  public:
    enum ContentType { Table, Cell };
    enum GroupState { Opened, Closed };

  public:
    PropertiesDock(QWidget *parent = 0);
   ~PropertiesDock();

    void setContentType(ContentType type);
    void addGroup(const QString &name, const QColor &color, const int row, const int rows);

    void standardValues();

    QTableWidgetItem *itemAt(unsigned int row, unsigned int column);

  public slots:
    void loadItemValues(QTableWidgetItem *item);
    void tableCellChanged(int row, int column);

  protected:
    // Common cell properties.
    QString       m_title;
    QString       m_value;
    bool          m_read_only;
    QString       m_format;
    QString       m_link_to;
    QString       m_tooltip;

    // Look and feel.
    QColor        m_color_text;
    QColor        m_color_background;
    unsigned int  m_h_alignment;
    unsigned int  m_v_alignment;

    // Borders and margins.
    unsigned int  m_margin_1;
    unsigned int  m_margin_2;
    unsigned int  m_margin_3;
    unsigned int  m_margin_4;
    unsigned int  m_border_size_1;
    unsigned int  m_border_size_2;
    unsigned int  m_border_size_3;
    unsigned int  m_border_size_4;
    unsigned int  m_border_style_1;
    unsigned int  m_border_style_2;
    unsigned int  m_border_style_3;
    unsigned int  m_border_style_4;
    QColor        m_border_color_1;
    QColor        m_border_color_2;
    QColor        m_border_color_3;
    QColor        m_border_color_4;

    QTableWidget     *m_table;
    QTableWidgetItem *m_item;
    ContentType       m_content_type;
    bool              m_loading;
};

