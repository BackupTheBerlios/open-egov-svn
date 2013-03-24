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

#include <QDebug>

void OEG_DebugMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &message);

namespace OEG { namespace Qt {

class DebugMessageHandler : public QObject
{
  Q_OBJECT

  public:
    enum DebugMessageType {
      Info = 0,
      Warning,
      Error,
      Debug,
    };

    enum DebugMessageTarget {
      COUT = 0,
      CERR,
      GUI,
      HIDE,
      FILE,
      MAILER,
      PRINTER,
    };

  public:
    DebugMessageHandler(QWidget *parent = 0);

  protected:

};

}}

