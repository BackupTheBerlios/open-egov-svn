# $Id$

TARGET       = oegMail
VERSION      = 1.0.0.0
QT          += 
PACKAGES     = GETTEXT

RC_FILE      = resources.rc
DEFINES     += 
INCLUDEPATH += ../..
LIBS        +=

FORMS       += forms/mail-editor.ui
HEADERS     += *.h
SOURCES     += *.cpp

include(../common.pri)

