# $Id$

TARGET    = "laws-and-regulations"
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
QT       += xml network
PACKAGES  = QT GETTEXT

include(..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}common.pri)

