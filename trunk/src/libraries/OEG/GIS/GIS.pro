# $Id$

TARGET       = oegGIS
VERSION      = 1.0.0.0
QT          += network xml widgets
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       +=
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

