# $Id$

TARGET       = oegPluginResistor
VERSION      = 1.0.0.0
QT          += gui
PACKAGES     = QT GETTEXT
INCLUDEPATH += ../../../applications/electronics/eperky/src
PLUGINSDIR   = eperky
SOURCES      = *.cpp
HEADERS      = *.h
FORMS        = 
RC_FILE      = resources.rc

include(../../common.pri)

