# $Id$

TEMPLATE     = app
CONFIG      += qt warn_on release
QT          += core gui xml
DESTDIR      = ../../../../../bin
INCLUDEPATH += ../../../../libraries
LIBS        += -L../../../../../bin -loegQt1

