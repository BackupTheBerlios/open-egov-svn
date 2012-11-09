@ECHO OFF

REM $Id$

CALL ENV.BAT

CD /D "%0"\..

ECHO Building libraries ...

IF EXIST src\libraries (
  ECHO src\libraries
  CD src\libraries
  qmake -recursive
  mingw32-make
  CD ..\..
)

ECHO Building applications ...

IF EXIST src\applications (
  ECHO src\applications
  CD src\applications
  qmake -recursive
  mingw32-make
  CD ..\..
)

ECHO Building plugins ...

IF EXIST src\plugins (
  ECHO src\plugins
  CD src\plugins
  qmake -recursive
  mingw32-make
  CD ..\..
)

ECHO Check output for errors!
PAUSE

