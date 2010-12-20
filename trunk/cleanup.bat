@ECHO OFF

REM $Id$

REM Look into C:\Qt\2010.05\bin\qtenv.bat for updated data.

set QTDIR=C:\Qt\2010.05\qt
set PATH=%QTDIR%\bin;%PATH%;C:\Qt\2010.05\mingw\bin;%SystemRoot%\System32
set QMAKESPEC=win32-g++


CD /D "%0"\..

ECHO Cleaning directory structure.

IF EXIST src\libraries (
  ECHO src\libraries
  CD src\libraries
  IF EXIST Makefile RD /S /Q Makefile
  qmake -recursive
  mingw32-make distclean
)

ECHO Check output for errors!
PAUSE

