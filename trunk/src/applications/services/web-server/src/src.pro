# $Id$

TARGET    = web-server
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
CONFIG   += release warn_on thread qt console
QT       -= gui widgets
QT       += network
PACKAGES  = QT GETTEXT

include(../../../common.pri)

