@ECHO OFF

REM $Id: cleanup.bat 355 2010-12-20 23:21:25Z gerrit-albrecht $

REM Look into C:\Qt\2010.05\bin\qtenv.bat for updated data.

set QTDIR=C:\Qt\2010.05\qt
set PATH=%QTDIR%\bin;%PATH%;C:\Qt\2010.05\mingw\bin;%SystemRoot%\System32
set QMAKESPEC=win32-g++


CD /D "%0"\..

ECHO Building libraries ...

IF EXIST src\libraries (
  ECHO src\libraries
  CD src\libraries
  qmake
  mingw32-make
  CD ..\..
)

ECHO Building applications ...

IF EXIST src\applications (
  ECHO src\applications
  CD src\applications
  qmake
  mingw32-make
  CD ..\..
)

ECHO Check output for errors!
PAUSE

