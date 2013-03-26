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
#include <QByteArray>

#include <QDebug>

#include <OEG/Mail/MimeType.h>

namespace OEG { namespace Mail {

class Attachment : public QObject
{
  Q_OBJECT

  public:
    enum ContentDisposition
      { DisplayInline, DisplayAttachment };

    enum ContentTransferEncoding
      { Encode7Bit, Encode8Bit, EncodeBinary, EncodeQuotedPrintable, EncodeBase64 };

  public:
    Attachment(QObject *parent = 0);
    virtual ~Attachment();

  protected:
    void clear();

  protected:
    QByteArray m_data;
    QString    m_file_name;
    QString    m_modification_date;
    MimeType   m_content_type;
};

}}

