# $Id$

# See Qt bugs #4329, #8430.
# With $$OUT_PWD we have a fixed point to start with.
# $$PWD contains only the pro/pri directory.

# $$OUT_PWD contains something like: C:/Test/123. Windows dislikes it.
contains(DIR_SEPARATOR, "\\") {
  PRO_OUT_PATH = $$replace(OUT_PWD, "/", "\\")
  #message($${PRO_OUT_PATH})
}
else {
  PRO_OUT_PATH = $$OUT_PWD
}

TEMPLATE     = app
CONFIG      += qt warn_on
QT          += core gui xml
DESTDIR      = $${PRO_OUT_PATH}$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin
INCLUDEPATH += ..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}libraries
QMAKE_LFLAGS += -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc

exists(../config.pri) {
  #message("File config.pri found and included!")
  include(../config.pri)
}
else {
  message("No config.pri found!")
}

MYDEBUGSUFFIX=""

debug {
  MYDEBUGSUFFIX=.debug
  TARGET = $${TARGET}$${MYDEBUGSUFFIX}
  message("TARGET is: $${TARGET}")
}

exists($$(TEMP)) {
  MYTEMPDIR=$$(TEMP)$${DIR_SEPARATOR}open-egovernment$${DIR_SEPARATOR}
  OBJECTS_DIR=$${MYTEMPDIR}$${TARGET}$${DIR_SEPARATOR}
  MOC_DIR=$${MYTEMPDIR}$${TARGET}$${DIR_SEPARATOR}
  #message("TEMP folder is: $$(TEMP)")
  #message("OBJ folder is: $${OBJECTS_DIR}")
}
else {
  MYTEMPDIR=""
  message("No TEMP environment variable found: TEMP=$$(TEMP)")
}

win32 {
  debug {
    QMAKE_POST_LINK += echo "debug: not stripped."
  }
  else {
    #QMAKE_POST_LINK += strip --strip-unneeded \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\"
    QMAKE_POST_LINK += strip --strip-unneeded -o \"$${MYTEMPDIR}$${TARGET}.stripped\" \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\" && MOVE /Y \"$${MYTEMPDIR}$${TARGET}.stripped\" \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\"
  }

  exists("$${DESTDIR}$${DIR_SEPARATOR}peflags.exe") {
    QMAKE_POST_LINK += "&&"
    #$${DESTDIR}$${DIR_SEPARATOR}$$replace(TARGET, " ", "\ ").exe
    QMAKE_POST_LINK += cd $${DESTDIR} && peflags.exe --dynamicbase=true --nxcompat=true \"$${TARGET}.exe\"
  }
  else {
    message("No peflags.exe found.")
  }
}

win32: DLLEXTENSION=dll
else:  DLLEXTENSION=so

isEmpty(PACKAGES) {
  PACKAGES += QT
}
# Want to avoid several -L but can't make them unique because "-L" should be placed in front of "-l".
LIBSLINE = -L..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin
contains(PACKAGES, QT) {
  message(Adding support for OEG-Qt ...)
  LIBSLINE += -loegQt$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegQt$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, CRYPT) {
  message(Adding support for OEG-Crypt ...)
  LIBSLINE += -loegCrypt$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegCrypt$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, GIS) {
  message(Adding support for OEG-GIS ...)
  LIBSLINE += -loegGIS$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegGIS$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, MATH) {
  message(Adding support for OEG-Math ...)
  LIBSLINE += -loegMath$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegMath$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, MAIL) {
  message(Adding support for OEG-Mail ...)
  LIBSLINE += -loegMail$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegMail$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, PAGES) {
  message(Adding support for OEG-Pages ...)
  LIBSLINE += -loegPages$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegPages$${MYDEBUGSUFFIX}1.a
}
contains(PACKAGES, 3D) {
  message(Adding support for OEG-3D ...)
  LIBSLINE += -loeg3D$${MYDEBUGSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboeg3D$${MYDEBUGSUFFIX}1.a
}
LIBS += $$LIBSLINE

contains(PACKAGES, GETTEXT) {
  message(Adding support for GNU gettext ...)

  # Needed to automatically include the gettext headers while using the OEG libraries.
  DEFINES += USE_GETTEXT

  win32 {
    INCLUDEPATH += ../../../../../include
    LIBS += -L../../../../../lib -lintl -lgettextpo
  }
}

win32 {
  #DEFINES += XP_WIN WIN32 _WIN32 _WINDOWS _MINGW
}

# win32:debug adds this CONFIG option even if only a release build gets compiled. Why?
win32 {
  debug {
    #CONFIG += console
  }
}

win32 {
  exists($${PRO_OUT_PATH}$${DIR_SEPARATOR}application.rc) {
    RC_FILE += application.rc
  }
  else {
    message("This Windows build is missing an application.rc!")
  }
}

# We don't use QRC files.
exists($${PRO_OUT_PATH}$${DIR_SEPARATOR}application.qrc) {
  RESOURCES += application.qrc
}

run.commands = @echo Running $${TARGET} && $${DESTDIR}$${DIR_SEPARATOR}$${TARGET}
QMAKE_EXTRA_TARGETS += run

