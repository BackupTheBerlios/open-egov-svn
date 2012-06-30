# $Id$

TEMPLATE     = lib
CONFIG      += plugin qt warn_on release
QT          += core gui
DESTDIR      = ../../../../plugins/$${PLUGINSDIR}
INCLUDEPATH += ../../../libraries

win32 {
# TODO: peflags, strip, sign.
}

exists($$(TEMP)) {
  MYTEMPDIR=$$(TEMP)$${DIR_SEPARATOR}open-egovernment$${DIR_SEPARATOR}
  OBJECTS_DIR=$${MYTEMPDIR}$${TARGETDIR}$${DIR_SEPARATOR}
  MOC_DIR=$${OBJECTS_DIR}
  RCC_DIR=$${OBJECTS_DIR}
  UI_DIR=$${OBJECTS_DIR}
  #message("TEMP folder is: $$(TEMP)")
  #message("OBJ folder is: $${OBJECTS_DIR}")
}
else {
  MYTEMPDIR=""
  message("No TEMP environment variable found: TEMP=$$(TEMP)")
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

