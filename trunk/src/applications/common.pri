# $Id$

TEMPLATE     = app
CONFIG      += qt warn_on release
QT          += core gui xml
DESTDIR      = ../../../../../bin
INCLUDEPATH += ../../../../libraries
LIBS        += -L../../../../../bin -loegQt1

win32-g++ {
  QMAKE_POST_LINK += strip \"$${DESTDIR}/$${TARGET}.exe\"
  exists($${DESTDIR}/peflags.exe) {
    #QMAKE_POST_LINK += && $${DESTDIR}/peflags.exe --dynamicbase=true --nxcompat=true $${DESTDIR}/$$replace(TARGET, " ", "\ ").exe 
    QMAKE_POST_LINK += && cd $${DESTDIR} && peflags.exe --dynamicbase=true --nxcompat=true \"$${TARGET}.exe\" 
  }
}

