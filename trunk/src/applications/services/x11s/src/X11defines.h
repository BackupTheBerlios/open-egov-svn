// $Id$
//
// Open eGovernment
// Copyright (C) 2004-2010 by Gerrit M. Albrecht
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

// Constant definitions used in the X11 protocol.

#pragma once

// X11 Request Opcodes.

#define XRQ_CREATE_WINDOW                1
#define XRQ_CHANGE_WINDOW_ATTRIBUTE      2
#define XRQ_GET_WINDOW_ATTRIBUTES        3
#define XRQ_DESTROY_WINDOW               4
#define XRQ_DESTROY_SUBWINDOWS           5
#define XRQ_CHANGE_SAVE_SET              6
#define XRQ_REPARENT_WINDOW              7
#define XRQ_MAP_WINDOW                   8
#define XRQ_MAP_SUBWINDOWS               9
#define XRQ_UNMAP_WINDOW                10
#define XRQ_UNMAP_SUBWINDOWS            11
#define XRQ_CONFIGURE_WINDOW            12
#define XRQ_CIRCULATE_WINDOW            13
#define XRQ_GET_GEOMETRY                14
#define XRQ_QUERY_TREE                  15
#define XRQ_INTERN_ATOM                 16
#define XRQ_GET_ATOM_NAME               17
#define XRQ_CHANGE_PROPERTY             18
#define XRQ_DELETE_PROPERTY             19
#define XRQ_GET_PROPERTY                20
#define XRQ_LIST_PROPERTIES             21
#define XRQ_SET_SELECTION_OWNER         22
#define XRQ_GET_SELECTION_OWNER         23
#define XRQ_CONVERT_SELECTION           24
#define XRQ_SEND_EVENT                  25
#define XRQ_GRAB_POINTER                26
#define XRQ_UNGRAB_POINTER              27
#define XRQ_GRAB_BUTTON                 28
#define XRQ_UNGRAB_BUTTON               29
#define XRQ_CHANGE_ACTIVE_POINTER_GRAB  30
#define XRQ_GRAB_KEYBOARD               31
#define XRQ_UNGRAB_KEYBOARD             32
#define XRQ_GRAB_KEY                    33
#define XRQ_UNGRAB_KEY                  34
#define XRQ_ALLOW_EVENTS                35
#define XRQ_GRAB_SERVER                 36
#define XRQ_UNGRAB_SERVER               37
#define XRQ_QUERY_POINTER               38
#define XRQ_GET_MOTION_EVENTS           39
#define XRQ_TRANSLATE_COORDINATES       40
#define XRQ_WARP_POINTER                41
#define XRQ_SET_INPUT_FOCUS             42
#define XRQ_GET_INPUT_FOCUS             43
#define XRQ_QUERY_KEYMAP                44
#define XRQ_OPEN_FONT                   45
#define XRQ_CLOSE_FONT                  46
#define XRQ_QUERY_FONT                  47
#define XRQ_QUERY_TEXT_EXTENTS          48
#define XRQ_LIST_FONTS                  49
#define XRQ_LIST_FONTS_WITH_INFO        50
#define XRQ_SET_FONT_PATH               51
#define XRQ_GET_FONT_PATH               52
#define XRQ_CREATE_PIXMAP               53
#define XRQ_FREE_PIXMAP                 54
#define XRQ_CREATE_GC                   55
#define XRQ_CHANGE_GC                   56
#define XRQ_COPY_GC                     57
#define XRQ_SET_DASHES                  58
#define XRQ_SET_CLIP_RECTANGLES         59
#define XRQ_FREE_GC                     60
#define XRQ_CLEAR_AREA                  61
#define XRQ_COPY_AREA                   62
#define XRQ_COPY_PLANE                  63
#define XRQ_POLY_POINT                  64
#define XRQ_POLY_LINE                   65
#define XRQ_POLY_SEGMENT                66
#define XRQ_POLY_RECTANGLE              67
#define XRQ_POLY_ARC                    68
#define XRQ_FILL_POLY                   69
#define XRQ_POLY_FILL_RECTANGLE         70
#define XRQ_POLY_FILL_ARC               71
#define XRQ_PUT_IMAGE                   72
#define XRQ_GET_IMAGE                   73
#define XRQ_POLY_TEXT_8                 74
#define XRQ_POLY_TEXT_16                75
#define XRQ_IMAGE_TEXT_8                76
#define XRQ_IMAGE_TEXT_16               77
#define XRQ_CREATE_COLORMAP             78
#define XRQ_FREE_COLORMAP               79
#define XRQ_COPY_COLORMAP_AND_FREE      80
#define XRQ_INSTALL_COLORMAP            81
#define XRQ_UNINSTALL_COLORMAP          82
#define XRQ_LIST_INSTALLED_COLORMAPS    83
#define XRQ_ALLOC_COLOR                 84
#define XRQ_ALLOC_NAMED_COLOR           85
#define XRQ_ALLOC_COLOR_CELLS           86
#define XRQ_ALLOC_COLOR_PLANES          87
#define XRQ_FREE_COLORS                 88
#define XRQ_STORE_COLORS                89
#define XRQ_STORE_NAMED_COLOR           90
#define XRQ_QUERY_COLORS                91
#define XRQ_LOOKUP_COLOR                92
#define XRQ_CREATE_CURSOR               93
#define XRQ_CREATE_GLYPH_CURSOR         94
#define XRQ_FREE_CURSOR                 95
#define XRQ_RECOLOR_CURSOR              96
#define XRQ_QUERY_BEST_SIZE             97
#define XRQ_QUERY_EXTENSION             98
#define XRQ_LIST_EXTENSIONS             99
#define XRQ_CHANGE_KEYBOARD_MAPPING    100
#define XRQ_GET_KEYBOARD_MAPPING       101
#define XRQ_CHANGE_KEYBOARD_CONTROL    102
#define XRQ_GET_KEYBOARD_CONTROL       103
#define XRQ_BELL                       104
#define XRQ_CHANGE_POINTER_CONTROL     105
#define XRQ_GET_POINTER_CONTROL        106
#define XRQ_SET_SCREEN_SAVER           107
#define XRQ_GET_SCREEN_SAVER           108
#define XRQ_CHANGE_HOSTS               109
#define XRQ_LIST_HOSTS                 110
#define XRQ_SET_ACCESS_CONTROL         111
#define XRQ_SET_CLOSE_DOWN_MODE        112
#define XRQ_KILL_CLIENT                113
#define XRQ_ROTATE_PROPERTIES          114
#define XRQ_FORCE_SCREEN_SAVER         115
#define XRQ_SET_POINTER_MAPPING        116
#define XRQ_GET_POINTER_MAPPING        117
#define XRQ_SET_MODIFIER_MAPPING       118
#define XRQ_GET_MODIFIER_MAPPING       119
#define XRQ_NO_OPERATION               127

// X11 Event Codes.

#define XEV_KEY_PRESS                    2
#define XEV_KEY_RELEASE                  3
#define XEV_BUTTON_PRESS                 4
#define XEV_BUTTON_RELEASE               5
#define XEV_MOTION_NOTIFY                6
#define XEV_ENTER_NOTIFY                 7
#define XEV_LEAVE_NOTIFY                 8
#define XEV_FOCUS_IN                     9
#define XEV_FOCUS_OUT                   10
#define XEV_KEYMAP_NOTIFY               11
#define XEV_EXPOSE                      12
#define XEV_GRAPHICS_EXPOSE             13
#define XEV_NO_EXPOSE                   14
#define XEV_VISIBILITY_NOTIFY           15
#define XEV_CREATE_NOTIFY               16
#define XEV_DESTROY_NOTIFY              17
#define XEV_UNMAP_NOTIFY                18
#define XEV_MAP_NOTIFY                  19
#define XEV_MAP_REQUEST                 20
#define XEV_REPARENT_NOTIFY             21
#define XEV_CONFIGURE_NOTIFY            22
#define XEV_CONFIGURE_REQUEST           23
#define XEV_GRAVITY_NOTIFY              24
#define XEV_RESIZE_REQUEST              25
#define XEV_CIRCULATE_NOTIFY            26
#define XEV_CIRCULATE_REQUEST           27
#define XEV_PROPERTY_NOTIFY             28
#define XEV_SELECTION_CLEAR             29
#define XEV_SELECTION_REQUEST           30
#define XEV_SELECTION_NOTIFY            31
#define XEV_COLORMAP_NOTIFY             32
#define XEV_CLIENT_MESSAGE              33
#define XEV_MAPPING_NOTIFY              34

// X11 Error Codes.

#define XEC_REQUEST                      1
#define XEC_VALUE                        2
#define XEC_WINDOW                       3
#define XEC_PIXMAP                       4
#define XEC_ATOM                         5
#define XEC_CURSOR                       6
#define XEC_FONT                         7
#define XEC_MATCH                        8
#define XEC_DRAWABLE                     9
#define XEC_ACCESS                      10
#define XEC_ALLOC                       11
#define XEC_COLORMAP                    12
#define XEC_GCONTEXT                    13
#define XEC_IDCHOICE                    14
#define XEC_NAME                        15
#define XEC_LENGTH                      16
#define XEC_IMPLEMENTATION              17

// Structs.

struct Request {        // Clients send them to a server.
};

struct Reply {          // Answer to a server's request.
};

struct Error {          // Answer to a server's request.
};

struct Event {          // A server can send events to a client independently of a request.
};

