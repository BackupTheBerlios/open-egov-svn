@ECHO OFF

REM $Id$

IF NOT EXIST E:\temp\NUL GOTO NO_E_DRIVE

ECHO TEMP=E:\temp
SET TEMP=E:\temp
SET TMP=E:\temp

:NO_E_DRIVE

ECHO Setting up environment for Qt usage...
SET QTDIR=C:\QtSDK\Desktop\Qt\4.8.1\mingw
SET PATH=%QTDIR%\bin;%PATH%
SET PATH=C:\QtSDK\mingw\bin;%PATH%
