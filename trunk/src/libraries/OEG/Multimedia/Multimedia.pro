# $Id$

TARGET       = oegMultimedia
VERSION      = 1.0.0.0
QT          += gui widgets multimedia
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       +=
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

