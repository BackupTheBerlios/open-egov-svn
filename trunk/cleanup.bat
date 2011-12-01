@ECHO OFF

REM $Id$

ECHO Start erfolgt aus einer Batch-Datei heraus.
ECHO Alle Ausgaben werden in "cleanup.log"
ECHO in diesem Verzeichnis umgeleitet.

CD /D %0\..

IF EXIST cleanup.log DEL /F /S /Q cleanup.log
cscript.exe //Nologo cleanup.vbs > cleanup.log

