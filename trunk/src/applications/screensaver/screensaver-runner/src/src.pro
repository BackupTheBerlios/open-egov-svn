# $Id$

TARGET    = screensaver-runner
SOURCES   = *.cpp
HEADERS   = *.h
FORMS     = 
QT        = core gui widgets
QT       -= xml
PACKAGES  = 
CONFIG   += console static

include(../../../common.pri)

LIBS      = C:\Qt\2010.04-static\qt\lib\libQtCore.a C:\Qt\2010.04-static\qt\lib\libQtGui.a

