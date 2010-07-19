# $Id$

TARGET    = builder
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
QT       += xml network
PACKAGES  = QT GETTEXT

CONFIG += console

include(..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}common.pri)

