# $Id$

TARGET       = oegEditor
VERSION      = 1.0.0.0
QT          += gui network xml widgets
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       += 
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

