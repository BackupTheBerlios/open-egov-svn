# $Id$

TARGET    = about-dialog
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = forms/*.ui
QT       += xml network widgets
PACKAGES  = QT GETTEXT

include(../../../common.pri)

