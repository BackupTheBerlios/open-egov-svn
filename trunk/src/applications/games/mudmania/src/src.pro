# $Id$

TARGET    = dictionary
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
QT       += sql network
PACKAGES  = QT GETTEXT

include(..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}common.pri)

