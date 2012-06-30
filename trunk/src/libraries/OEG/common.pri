# $Id$

TEMPLATE  = lib
CONFIG   += qt warn_on
QT       += core
#dbus
DESTDIR   = ../../../../bin
QMAKE_LFLAGS += -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc
#CONFIG += qdbus

exists(../../config.pri) {
  #message("File config.pri found and included!")
  include(../../config.pri)
}
else {
  message("No config.pri found!")
}

debug {
  MYTARGETSUFFIX=.debug
  TARGETDIR=$${TARGET}$${MYTARGETSUFFIX}
  TARGET=$${TARGET}$${MYTARGETSUFFIX}
  #message("TARGET is: $${TARGET}")
}
else:release {
  MYTARGETSUFFIX=""
  TARGETDIR="$${TARGET}.release"
  TARGET=$${TARGET}
  #message("TARGET is: $${TARGET}")
}

exists($$(TEMP)) {
  MYTEMPDIR=$$(TEMP)$${DIR_SEPARATOR}open-egovernment$${DIR_SEPARATOR}
  OBJECTS_DIR=$${MYTEMPDIR}$${TARGETDIR}$${DIR_SEPARATOR}
  MOC_DIR=$${MYTEMPDIR}$${TARGETDIR}$${DIR_SEPARATOR}
  #message("TEMP folder is: $$(TEMP)")
  #message("OBJ folder is: $${OBJECTS_DIR}")
}
else {
  MYTEMPDIR=""
  message("No TEMP environment variable found: TEMP=$$(TEMP)")
}

# $$OUT_PWD contains the directory of our .pro file with slashes
# like: C:/Test/123. Windows dislikes such paths. We could use
# "DESTDIR = ../../../../bin" but relative paths depend on the file
# (pro/pri) where they are noted. An absolute path is needed to
# call peflags from the bin directory. It is build using OUT_PWD
# but with correct slashes/backslashes. The target name is
# hard-coded (version number). Need a better solution...

win32 {
  BINDIR  = $${OUT_PWD}/$${DESTDIR}
  contains(DIR_SEPARATOR, "\\") {
    BINDIR = $$replace(BINDIR, "/", "\\")
  }
  PEFLAGS = $${BINDIR}$${DIR_SEPARATOR}peflags.exe
  exists($${PEFLAGS}) {
    QMAKE_POST_LINK = \"$${PEFLAGS}\" --dynamicbase=true --nxcompat=true \"$${BINDIR}$${DIR_SEPARATOR}$${TARGET}1.dll\"
  }
  else {
    warning("No peflags.exe found.")
  }
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

