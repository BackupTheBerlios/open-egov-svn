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

// Every derived class can add a similar calcHash() method using this template.
// Needed a static calcHash() method but this wanted an object which has to be
// generated by an object factory (which returns SHA1, Adler32, ... objects).
// But its not possible to create a static and virtual method in C++ and using
// only static methods was not possible because of the linkage - the method
// HashAlgorithm::calcHash() was not able to access e.g. Adler32::createObject().

template <class T>
class HashAlgorithmStaticMethods {
  public:
    inline static QString calcHash(const QByteArray &data) {
      T *ha = new T();
      if (! ha)
        return "";
      ha->hash(data);
      QString result = ha->result();
      delete ha;
      return result;
    }
};

class HashAlgorithm : public QObject
{
  Q_OBJECT

  public:
    HashAlgorithm();
    HashAlgorithm(const HashAlgorithm &ha);
    ~HashAlgorithm();

    virtual void hash(const QByteArray &data) = 0;
    void hash(const QString &fileName);
    void hash(QFile &file);

    virtual void initialize();
    virtual void finalize();

    QString result();
    QString hashAlgorithmName() const;

    bool isLittleEndian();

  protected:
    bool    m_finalized;
    quint32 m_value;
    QString m_result;
    QString m_hash_algorithm_name;
};

