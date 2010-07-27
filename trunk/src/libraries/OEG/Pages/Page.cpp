// $Id$
//
// Open-eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#include <OEG/Pages/Page.h>

#include <QString>

using namespace OEG::Pages;
using namespace Qt;

Page::Page(QWidget *parent /*=0*/)
 : QWidget(parent)
{
  m_paper_format = A4;
  m_resolution   = 600;
  m_fg_color     = Qt::black;
  m_bg_color     = Qt::white;
}

Page::~Page()
{
}

void Page::writeText(unsigned long int x, unsigned long int y, const QString &text)
{
}

void Page::drawLine(unsigned long int x1, unsigned long int y1,
                    unsigned long int x2, unsigned long int y2)
{
}

void Page::setPaperFormat(const PaperFormat paperFormat)
{
  m_paper_format = paperFormat;
}

Page::PaperFormat Page::paperFormat() const
{
  return m_paper_format;
}

void Page::setResolution(const unsigned int resolution)
{
  m_resolution = resolution;
}

unsigned int Page::resolution() const
{
  return m_resolution;
}

void Page::setFgColor(const QColor color)
{
  m_fg_color = color;
}

QColor Page::fgColor() const
{
  return m_fg_color;
}

void Page::setBgColor(const QColor color)
{
  m_bg_color = color;
}

QColor Page::bgColor() const
{
  return m_bg_color;
}

