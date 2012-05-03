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
#include <QDebug>

#include "Request.h"

class Connection;

class Error : public QObject
{
  Q_OBJECT

  public:
    enum ErrorCode {
      XEC_NO_ERROR                   =  0,
      XEC_REQUEST                    =  1,
      XEC_VALUE                      =  2,
      XEC_WINDOW                     =  3,
      XEC_PIXMAP                     =  4,
      XEC_ATOM                       =  5,
      XEC_CURSOR                     =  6,
      XEC_FONT                       =  7,
      XEC_MATCH                      =  8,
      XEC_DRAWABLE                   =  9,
      XEC_ACCESS                     = 10,
      XEC_ALLOC                      = 11,
      XEC_COLORMAP                   = 12,
      XEC_GCONTEXT                   = 13,
      XEC_IDCHOICE                   = 14,
      XEC_NAME                       = 15,
      XEC_LENGTH                     = 16,
      XEC_IMPLEMENTATION             = 17
    };

  public:
    Error(QObject *parent=0);
    virtual ~Error();

    static void writeError(Connection *connection, ErrorCode errorcode, Request::RequestOpcode opcode, int id=0);

  private:

};

