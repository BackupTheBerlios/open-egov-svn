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

class Request : public QObject
{
  Q_OBJECT

  public:
    enum RequestOpcode {
      XRQ_CREATE_WINDOW              =   1,
      XRQ_CHANGE_WINDOW_ATTRIBUTE    =   2,
      XRQ_GET_WINDOW_ATTRIBUTES      =   3,
      XRQ_DESTROY_WINDOW             =   4,
      XRQ_DESTROY_SUBWINDOWS         =   5,
      XRQ_CHANGE_SAVE_SET            =   6,
      XRQ_REPARENT_WINDOW            =   7,
      XRQ_MAP_WINDOW                 =   8,
      XRQ_MAP_SUBWINDOWS             =   9,
      XRQ_UNMAP_WINDOW               =  10,
      XRQ_UNMAP_SUBWINDOWS           =  11,
      XRQ_CONFIGURE_WINDOW           =  12,
      XRQ_CIRCULATE_WINDOW           =  13,
      XRQ_GET_GEOMETRY               =  14,
      XRQ_QUERY_TREE                 =  15,
      XRQ_INTERN_ATOM                =  16,
      XRQ_GET_ATOM_NAME              =  17,
      XRQ_CHANGE_PROPERTY            =  18,
      XRQ_DELETE_PROPERTY            =  19,
      XRQ_GET_PROPERTY               =  20,
      XRQ_LIST_PROPERTIES            =  21,
      XRQ_SET_SELECTION_OWNER        =  22,
      XRQ_GET_SELECTION_OWNER        =  23,
      XRQ_CONVERT_SELECTION          =  24,
      XRQ_SEND_EVENT                 =  25,
      XRQ_GRAB_POINTER               =  26,
      XRQ_UNGRAB_POINTER             =  27,
      XRQ_GRAB_BUTTON                =  28,
      XRQ_UNGRAB_BUTTON              =  29,
      XRQ_CHANGE_ACTIVE_POINTER_GRAB =  30,
      XRQ_GRAB_KEYBOARD              =  31,
      XRQ_UNGRAB_KEYBOARD            =  32,
      XRQ_GRAB_KEY                   =  33,
      XRQ_UNGRAB_KEY                 =  34,
      XRQ_ALLOW_EVENTS               =  35,
      XRQ_GRAB_SERVER                =  36,
      XRQ_UNGRAB_SERVER              =  37,
      XRQ_QUERY_POINTER              =  38,
      XRQ_GET_MOTION_EVENTS          =  39,
      XRQ_TRANSLATE_COORDINATES      =  40,
      XRQ_WARP_POINTER               =  41,
      XRQ_SET_INPUT_FOCUS            =  42,
      XRQ_GET_INPUT_FOCUS            =  43,
      XRQ_QUERY_KEYMAP               =  44,
      XRQ_OPEN_FONT                  =  45,
      XRQ_CLOSE_FONT                 =  46,
      XRQ_QUERY_FONT                 =  47,
      XRQ_QUERY_TEXT_EXTENTS         =  48,
      XRQ_LIST_FONTS                 =  49,
      XRQ_LIST_FONTS_WITH_INFO       =  50,
      XRQ_SET_FONT_PATH              =  51,
      XRQ_GET_FONT_PATH              =  52,
      XRQ_CREATE_PIXMAP              =  53,
      XRQ_FREE_PIXMAP                =  54,
      XRQ_CREATE_GC                  =  55,
      XRQ_CHANGE_GC                  =  56,
      XRQ_COPY_GC                    =  57,
      XRQ_SET_DASHES                 =  58,
      XRQ_SET_CLIP_RECTANGLES        =  59,
      XRQ_FREE_GC                    =  60,
      XRQ_CLEAR_AREA                 =  61,
      XRQ_COPY_AREA                  =  62,
      XRQ_COPY_PLANE                 =  63,
      XRQ_POLY_POINT                 =  64,
      XRQ_POLY_LINE                  =  65,
      XRQ_POLY_SEGMENT               =  66,
      XRQ_POLY_RECTANGLE             =  67,
      XRQ_POLY_ARC                   =  68,
      XRQ_FILL_POLY                  =  69,
      XRQ_POLY_FILL_RECTANGLE        =  70,
      XRQ_POLY_FILL_ARC              =  71,
      XRQ_PUT_IMAGE                  =  72,
      XRQ_GET_IMAGE                  =  73,
      XRQ_POLY_TEXT_8                =  74,
      XRQ_POLY_TEXT_16               =  75,
      XRQ_IMAGE_TEXT_8               =  76,
      XRQ_IMAGE_TEXT_16              =  77,
      XRQ_CREATE_COLORMAP            =  78,
      XRQ_FREE_COLORMAP              =  79,
      XRQ_COPY_COLORMAP_AND_FREE     =  80,
      XRQ_INSTALL_COLORMAP           =  81,
      XRQ_UNINSTALL_COLORMAP         =  82,
      XRQ_LIST_INSTALLED_COLORMAPS   =  83,
      XRQ_ALLOC_COLOR                =  84,
      XRQ_ALLOC_NAMED_COLOR          =  85,
      XRQ_ALLOC_COLOR_CELLS          =  86,
      XRQ_ALLOC_COLOR_PLANES         =  87,
      XRQ_FREE_COLORS                =  88,
      XRQ_STORE_COLORS               =  89,
      XRQ_STORE_NAMED_COLOR          =  90,
      XRQ_QUERY_COLORS               =  91,
      XRQ_LOOKUP_COLOR               =  92,
      XRQ_CREATE_CURSOR              =  93,
      XRQ_CREATE_GLYPH_CURSOR        =  94,
      XRQ_FREE_CURSOR                =  95,
      XRQ_RECOLOR_CURSOR             =  96,
      XRQ_QUERY_BEST_SIZE            =  97,
      XRQ_QUERY_EXTENSION            =  98,
      XRQ_LIST_EXTENSIONS            =  99,
      XRQ_CHANGE_KEYBOARD_MAPPING    = 100,
      XRQ_GET_KEYBOARD_MAPPING       = 101,
      XRQ_CHANGE_KEYBOARD_CONTROL    = 102,
      XRQ_GET_KEYBOARD_CONTROL       = 103,
      XRQ_BELL                       = 104,
      XRQ_CHANGE_POINTER_CONTROL     = 105,
      XRQ_GET_POINTER_CONTROL        = 106,
      XRQ_SET_SCREEN_SAVER           = 107,
      XRQ_GET_SCREEN_SAVER           = 108,
      XRQ_CHANGE_HOSTS               = 109,
      XRQ_LIST_HOSTS                 = 110,
      XRQ_SET_ACCESS_CONTROL         = 111,
      XRQ_SET_CLOSE_DOWN_MODE        = 112,
      XRQ_KILL_CLIENT                = 113,
      XRQ_ROTATE_PROPERTIES          = 114,
      XRQ_FORCE_SCREEN_SAVER         = 115,
      XRQ_SET_POINTER_MAPPING        = 116,
      XRQ_GET_POINTER_MAPPING        = 117,
      XRQ_SET_MODIFIER_MAPPING       = 118,
      XRQ_GET_MODIFIER_MAPPING       = 119,
      XRQ_NO_OPERATION               = 127
    };

  public:
    Request(QObject *parent=0);
    virtual ~Request();

  private:
    int  m_opcode;
};

