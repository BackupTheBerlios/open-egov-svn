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

#include <OEG/Common.h>

#include <QObject>

class Language : public QObject
{
  Q_OBJECT

  public:
    Language(QObject *parent = 0);

    int     m_id;
    QString m_value;
    QString m_alpha2code;
    QString m_alpha3codeb;
    QString m_alpha3codet;
    int     m_dictionary;
    int     m_scope;
    int     m_type;
    int     m_translation_id;

  protected:

  private slots:

  private:

};

