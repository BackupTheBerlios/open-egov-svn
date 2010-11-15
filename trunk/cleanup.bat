@ECHO OFF

REM $Id$

CD /D "%0"\..\

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

