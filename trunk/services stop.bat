@ECHO OFF

REM $Id$

REM Stops all services and apps from the start script.

CD /D "%0"\..\bin

ECHO Stopping services ...

ECHO. D-Bus



ECHO. MySQL



ECHO Finished (window closes in 10 seconds).
ping -n 11 localhost >nul

