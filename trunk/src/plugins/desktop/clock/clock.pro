# $Id$

TARGET       = oegPluginClock
VERSION      = 1.0.0.0
QT          += gui
PACKAGES     = QT GETTEXT
INCLUDEPATH += ../../../applications/components/desktop/src
PLUGINSDIR   = desktop
SOURCES      = *.cpp
HEADERS      = *.h
FORMS        = 
RC_FILE      = resources.rc

include(../../common.pri)

