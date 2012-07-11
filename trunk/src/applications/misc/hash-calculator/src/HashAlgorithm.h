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

#include <OEG/Common.h>

#include <QObject>
#include <QByteArray>
#include <QFile>

class HashAlgorithm : public QObject
{
  Q_OBJECT

  public:
    HashAlgorithm();
    HashAlgorithm(const HashAlgorithm &ha);
    ~HashAlgorithm();

    virtual QString hash(const QByteArray &data) = 0;
    QString hash(const QString &fileName);
    QString hash(QFile &file);

    virtual void initialize();
    virtual void finalize();

    QString result();
    QString hashAlgorithmName() const;

  protected:
    bool    m_finalized;
    quint32 m_value;
    QString m_result;
    QString m_hash_algorithm_name;
};

