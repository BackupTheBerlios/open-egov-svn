# $Id$

TARGET    = web-server
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
CONFIG   += thread console
QT       -= gui widgets
QT       += network
PACKAGES  = QT GETTEXT

include(../../../common.pri)

