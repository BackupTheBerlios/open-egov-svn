# $Id:$

TEMPLATE     = lib
CONFIG      += plugin qt warn_on release
QT          += core gui
DESTDIR      = ../../../../plugins/$${PLUGINSDIR}
INCLUDEPATH += ../../../libraries

win32 {
# TODO: peflags, strip, sign.
}

contains(PACKAGES, GETTEXT) {
  message(Adding support for GNU gettext ...)

  # Needed to automatically include the gettext headers while using the OEG libraries.
  DEFINES += USE_GETTEXT

  win32 {
    INCLUDEPATH += ../../../../include
    LIBS += -L../../../../lib -lintl -lgettextpo
  }
}

