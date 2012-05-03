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

// A server can send events to a client independently of a request.

class Event : public QObject
{
  Q_OBJECT

  public:
    enum EventCode {
      XEV_KEY_PRESS                  =  2,
      XEV_KEY_RELEASE                =  3,
      XEV_BUTTON_PRESS               =  4,
      XEV_BUTTON_RELEASE             =  5,
      XEV_MOTION_NOTIFY              =  6,
      XEV_ENTER_NOTIFY               =  7,
      XEV_LEAVE_NOTIFY               =  8,
      XEV_FOCUS_IN                   =  9,
      XEV_FOCUS_OUT                  = 10,
      XEV_KEYMAP_NOTIFY              = 11,
      XEV_EXPOSE                     = 12,
      XEV_GRAPHICS_EXPOSE            = 13,
      XEV_NO_EXPOSE                  = 14,
      XEV_VISIBILITY_NOTIFY          = 15,
      XEV_CREATE_NOTIFY              = 16,
      XEV_DESTROY_NOTIFY             = 17,
      XEV_UNMAP_NOTIFY               = 18,
      XEV_MAP_NOTIFY                 = 19,
      XEV_MAP_REQUEST                = 20,
      XEV_REPARENT_NOTIFY            = 21,
      XEV_CONFIGURE_NOTIFY           = 22,
      XEV_CONFIGURE_REQUEST          = 23,
      XEV_GRAVITY_NOTIFY             = 24,
      XEV_RESIZE_REQUEST             = 25,
      XEV_CIRCULATE_NOTIFY           = 26,
      XEV_CIRCULATE_REQUEST          = 27,
      XEV_PROPERTY_NOTIFY            = 28,
      XEV_SELECTION_CLEAR            = 29,
      XEV_SELECTION_REQUEST          = 30,
      XEV_SELECTION_NOTIFY           = 31,
      XEV_COLORMAP_NOTIFY            = 32,
      XEV_CLIENT_MESSAGE             = 33,
      XEV_MAPPING_NOTIFY             = 34
    };

  public:
    Event(QObject *parent=0);
    virtual ~Event();

  private:

};

