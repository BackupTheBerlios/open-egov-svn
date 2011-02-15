# $Id: src.pro 227 2010-08-04 18:13:48Z gerrit-albrecht $

TARGET    = suchfuxx
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
QT       += 
PACKAGES  = QT GETTEXT
CONFIG   += console

include(../../../common.pri)

#RESOURCES += icons.qrc
#INCLUDEPATH += ..
#CONFIG += debug_and_release build_all console
#MOC_DIR = tmp
#RCC_DIR = tmp
#UI_DIR  = tmp
#CONFIG( debug, debug|release ) {
#    OBJECTS_DIR = tmp/debug
#    DESTDIR = debug
#} else {
#    OBJECTS_DIR = tmp/release
#    DESTDIR = release
#}
#
#win32-msvc* {
#    QMAKE_CXXFLAGS += -Fd\$(IntDir)
#}

