# $Id$

TARGET       = oegcrypt
TEMPLATE     = lib
VERSION      = 1.0.0.0

CONFIG      += qt warn_on release
QT          += core
QT          -= gui
RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=
DESTDIR      = ../../../../bin

FORMS       +=
HEADERS     += *.h
SOURCES     += *.cpp

