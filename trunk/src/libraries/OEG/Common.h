// $Id$

#pragma once


#ifdef USE_GETTEXT

#include <libintl.h>
#include <locale.h>

#define _(text) gettext(text)

//#define _(text) (text)

#endif

