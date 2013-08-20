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
QT          += core gui widgets xml
DESTDIR      = $${PRO_OUT_PATH}$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin
DESTDIRTOOLS  = $${DESTDIR}.tools
INCLUDEPATH += ..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}libraries
QMAKE_LFLAGS += -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc

# If console flag was explicitly given, then use console always!
# Ignore console flag for release builds.

contains(CONFIG, console) {
  message(Compiling with console flag...)
}
else {
  release {
    CONFIG -= console
  }
}

exists(../config.pri) {
  #message("File config.pri found and included!")
  include(../config.pri)
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

win32 {
  debug {
    QMAKE_POST_LINK += echo "debug: not stripped."
  }
  else {
    #QMAKE_POST_LINK += strip --strip-unneeded \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\"
    QMAKE_POST_LINK += strip --strip-unneeded -o \"$${MYTEMPDIR}$${TARGET}.stripped\" \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\" && MOVE /Y \"$${MYTEMPDIR}$${TARGET}.stripped\" \"$${DESTDIR}$${DIR_SEPARATOR}$${TARGET}.exe\"
  }

  exists("$${DESTDIRTOOLS}$${DIR_SEPARATOR}peflags.exe") {
    QMAKE_POST_LINK += "&&"
    #$${DESTDIR}$${DIR_SEPARATOR}$$replace(TARGET, " ", "\ ").exe
    QMAKE_POST_LINK += cd $${DESTDIR} && "$${DESTDIRTOOLS}$${DIR_SEPARATOR}peflags.exe" --dynamicbase=true --nxcompat=true \"$${TARGET}.exe\"
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
  LIBSLINE += -loegQt$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegQt$${MYTARGETSUFFIX}1.a

  QT += network
}
contains(PACKAGES, CRYPT) {
  message(Adding support for OEG-Crypt ...)
  LIBSLINE += -loegCrypt$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegCrypt$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, CONTACTS) {
  message(Adding support for OEG-Contacts ...)
  LIBSLINE += -loegContacts$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegContacts$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, GIS) {
  message(Adding support for OEG-GIS ...)
  LIBSLINE += -loegGIS$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegGIS$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, MATH) {
  message(Adding support for OEG-Math ...)
  LIBSLINE += -loegMath$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegMath$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, MAIL) {
  message(Adding support for OEG-Mail ...)
  LIBSLINE += -loegMail$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegMail$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, PAGES) {
  message(Adding support for OEG-Pages ...)
  LIBSLINE += -loegPages$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboegPages$${MYTARGETSUFFIX}1.a
}
contains(PACKAGES, 3D) {
  message(Adding support for OEG-3D ...)
  LIBSLINE += -loeg3D$${MYTARGETSUFFIX}1
  PRE_TARGETDEPS += $${DESTDIR}/liboeg3D$${MYTARGETSUFFIX}1.a
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

