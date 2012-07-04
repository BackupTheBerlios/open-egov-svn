# $Id$

TARGET       = oegQt
VERSION      = 1.0.0.0
QT          += gui network
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       += forms/*.ui
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

