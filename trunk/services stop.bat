@ECHO OFF

REM $Id$

REM Stops all services and apps from the start script.

CD /D "%0"\..\bin

ECHO Stopping apps ...

ECHO MySQL



ECHO D-Bus



ECHO Finished.
PAUSE

