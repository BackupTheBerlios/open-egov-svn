// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <OEG/Common.h>

#include <QtCore>
#include <QtNetwork>

#include "WebPage.h"

WebPage::WebPage(QObject *parent)
 : QObject(parent)
{
  clear();
}

void WebPage::clear()
{
  m_source     = "";
  m_title      = "";
  m_contents   = "";
  m_need_build = true;

  m_http_header.clear();
  m_head.clear();
}

void WebPage::setHttpHeaderLine(const QString &s)
{
  if (s.length() > 0) {
    m_http_header << s;
  }
}

QString WebPage::httpHeader() const
{
  return m_http_header.join("\r\n");
}

void WebPage::build()
{
  QString s;

  s += "<html><head>";
  s += m_head.join("");
  s += "<title>" + m_title + "</title>";
  s += "</head>\n";
  s += "<body>" + m_contents + "</body></html>";

  m_source = s;
  m_need_build = false;
}

QString WebPage::source() const
{
  return m_source;
}

unsigned int WebPage::length() const
{
  return m_source.length();
}

void WebPage::setTitle(const QString &title)
{
  m_title = title;
  m_need_build = true;
}

void WebPage::setContents(const QString &contents)
{
  m_contents = contents;
  m_need_build = true;
}

