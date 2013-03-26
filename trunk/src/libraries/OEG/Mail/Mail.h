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

#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

#include <QDebug>

#include <OEG/Mail/MimeType.h>

namespace OEG { namespace Mail {

class Attachment;

class Mail : public QObject
{
  Q_OBJECT

  public:
    Mail(QObject *parent = 0);
    virtual ~Mail();

    Attachment *attachment(int n);
    void addAttachment(const Attachment *attachment);
    Attachment *newAttachment();

    QStringList headers(const QString &name = "") const;
    void setHeaders(const QStringList &headers);
    void addHeaders(const QStringList &headers);

    QStringList text();

  protected:
    void clear();

  protected:
    QList<Attachment *>  m_attachments;
    MimeType             m_content_type;
    QStringList          m_headers;
};

}}

