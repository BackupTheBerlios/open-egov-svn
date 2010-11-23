// $Id$
//
// Open eGovernment
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

#include <OEG/Mail/MimeType.h>

using namespace OEG::Mail;
using namespace Qt;

MimeType::MimeType(const QString &type /*=""*/, const QString &sub_type /*=""*/, QObject *parent /*=0*/)
 : QObject(parent)
{
  m_type     = type;
  m_sub_type = sub_type;
}

QString MimeType::text()
{
  if ((m_type.size() > 0) && (m_sub_type.size() > 0))
    return m_type + "/" + m_sub_type;

  return "";
}

