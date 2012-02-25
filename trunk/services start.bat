@ECHO OFF

REM $Id$

REM Starts all services and apps needed to work with OEG applications.

CD /D "%0"\..
IF EXIST "services config.bat" CALL "services config.bat"
CD bin

ECHO Starting services ...

IF "%USE_DBUS%" == "YES" (
  ECHO. D-Bus ^(R^)

) ELSE (
  ECHO. D-Bus ^(I^)

)

IF "%USE_MYSQL%" == "YES" (
  ECHO. MySQL ^(R^)

) ELSE (
  ECHO. MySQL ^(I^)

)

ECHO Finished (window closes in 10 seconds).
ping -n 11 localhost >nul

