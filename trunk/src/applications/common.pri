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
CONFIG      += qt warn_on release -debug
QT          += core gui xml
DESTDIR      = $${PRO_OUT_PATH}$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin
INCLUDEPATH += ..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}libraries

win32 {
  QMAKE_POST_LINK += strip --strip-unneeded \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\"
  exists("$${DESTDIR}$${DIR_SEPARATOR}peflags.exe") {
    #QMAKE_POST_LINK += && $${DESTDIR}$${DIR_SEPARATOR}peflags.exe --dynamicbase=true --nxcompat=true $${DESTDIR}$${DIR_SEPARATOR}$$replace(TARGET, " ", "\ ").exe
    QMAKE_POST_LINK += && cd $${DESTDIR} && peflags.exe --dynamicbase=true --nxcompat=true \"$${TARGET}.exe\"
  }
  else {
    message("No peflags.exe found.")
  }
}

isEmpty(PACKAGES) {
  PACKAGES += QT
}
# Want to avoid several -L but can't make them unique because "-L" should be placed in front of "-l".
LIBSLINE = -L..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin
contains(PACKAGES, QT) {
  message(Adding support for OEG-Qt ...)
  LIBSLINE += -loegQt1
}
contains(PACKAGES, CRYPT) {
  message(Adding support for OEG-Crypt ...)
  LIBSLINE += -loegCrypt1
}
contains(PACKAGES, MATH) {
  message(Adding support for OEG-Math ...)
  LIBSLINE += -loegMath1
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

exists($${PRO_OUT_PATH}$${DIR_SEPARATOR}application.qrc) {
  RESOURCES += application.qrc
}

run.commands = @echo Running $${TARGET} && $${DESTDIR}$${DIR_SEPARATOR}$${TARGET}
QMAKE_EXTRA_TARGETS += run
