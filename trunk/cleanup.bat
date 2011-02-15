@ECHO OFF

REM $Id$

ECHO Start erfolgt aus einer Batch-Datei heraus.
ECHO Alle Ausgaben werden in "log.txt"
ECHO in diesem Verzeichnis umgeleitet.

CD /D %0\..

IF EXIST log.txt DEL /F /S /Q log.txt
cscript.exe //Nologo cleanup.vbs > log.txt

