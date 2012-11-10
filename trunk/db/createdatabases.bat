@ECHO OFF

REM $Id$

CD /D %0\..
CD

..\env.bat

mingw32-make

PAUSE

