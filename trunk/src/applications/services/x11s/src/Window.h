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

#include <QWidget>

#include "Resource.h"

class Connection;

class Window : public Resource
{
  Q_OBJECT

  public:
    enum ObscureFlag {
      Unobscured             = 0,
      PartiallyObscured      = 1,
      FullyObscured          = 2,
      NotViewable            = 3
    };

    enum AttrFlag {
      AttrBackgroundPixmap   = 0,
      AttrBackgroundPixel    = 1,
      AttrBorderPixmap       = 2,
      AttrBorderPixel        = 3,
      AttrBitGravity         = 4,
      AttrWinGravity         = 5,
      AttrBackingStore       = 6,
      AttrBackingPlanes      = 7,
      AttrBackingPixel       = 8,
      AttrOverrideRedirect   = 9,
      AttrSaveUnder          = 10,
      AttrEventMask          = 11,
      AttrDoNotPropagateMask = 12,
      AttrColormap           = 13,
      AttrCursor             = 14
    };

    enum WindowGravityFlag {
      WindowGravityUnmap = 0,
      WindowGravityNorthWest = 1,
      WindowGravityNorth = 2,
      WindowGravityNorthEast = 3,
      WindowGravityWest = 4,
      WindowGravityCenter = 5,
      WindowGravityEast = 6,
      WindowGravitySouthWest = 7,
      WindowGravitySouth = 8,
      WindowGravitySouthEast = 9,
      WindowGravityStatic = 10
    };

  public:
    Window(QObject *parent=0);
    virtual ~Window();

    static void requestCreateWindow(Connection *connection);
    static void requestChangeWindowAttribute(Connection *connection);
    static void requestGetWindowAttributes(Connection *connection);
    static void requestDestroyWindow(Connection *connection);
    static void requestDestroySubWindows(Connection *connection);

  private:
    QWidget *m_window;
};

