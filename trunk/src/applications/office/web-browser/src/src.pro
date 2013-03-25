# $Id$

TARGET     = web-browser
SOURCES    = *.cpp
HEADERS    = *.h
FORMS      = forms/*.ui
CONFIG    += release warn_on thread qt console
QT        += gui network widgets xml
RESOURCES += application.qrc
PACKAGES   = QT GETTEXT

include(../../../common.pri)

