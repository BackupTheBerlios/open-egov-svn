# $Id$

TARGET       = oegVR
VERSION      = 1.0.0.0
QT          += gui opengl
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       +=
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

