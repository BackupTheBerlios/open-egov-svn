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

#include <OEG/Mail/Attachment.h>
#include <OEG/Mail/Mail.h>

using namespace OEG::Mail;
using namespace Qt;

Mail::Mail(QObject *parent /*=0*/)
 : QObject(parent)
{
}

Mail::~Mail()
{
  clear();
}

void Mail::clear()
{
  while (! m_attachments.isEmpty())
     delete m_attachments.takeFirst();

  m_headers.clear();
}

Attachment *Mail::attachment(int n)
{
  if (m_attachments.count() > n)
    return m_attachments.at(n);

  return 0;
}

void Mail::addAttachment(const Attachment *attachment)
{
  if (! attachment)
    return;

  m_attachments << const_cast<Attachment *>(attachment);
}

Attachment *Mail::newAttachment()
{
  Attachment *a = new Attachment(this);

  m_attachments << a;

  return a;
}

QStringList Mail::headers(const QString &name /*=""*/) const
{
  if (name.length() <= 0)
    return m_headers;

  return m_headers.filter(name, Qt::CaseSensitive);
}

void Mail::setHeaders(const QStringList &headers)
{
  m_headers = headers;
}

void Mail::addHeaders(const QStringList &headers)
{
  if (headers.count() > 0)
    m_headers += headers;
}

QStringList Mail::text()
{
  QStringList text;
  QString s;

  text << m_headers;
  s = "Content-Type: " + m_content_type.text();
  text << s;
  //m_attachments

  return text;
}

