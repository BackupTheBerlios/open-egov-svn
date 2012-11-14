@ECHO OFF

REM $Id$

REM Redirect temporary directory. Needed if you want to work from a (slow)
REM USB stick and store intermediate temporary files on the hard disk.

IF NOT EXIST D:\temp\NUL GOTO NO_D_DRIVE

ECHO TEMP=D:\temp
SET TEMP=D:\temp
SET TMP=D:\temp

GOTO TEMP_FOUND
:NO_D_DRIVE

IF NOT EXIST E:\temp\NUL GOTO NO_E_DRIVE

ECHO TEMP=E:\temp
SET TEMP=E:\temp
SET TMP=E:\temp

GOTO TEMP_FOUND
:NO_E_DRIVE

:TEMP_FOUND

REM Setting up environment variables.

ECHO Setting up environment for Qt usage...

REM Look into C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\qtenv2.bat and
REM C:\Qt\4.8.4\bin\qtvars.bat for updated data.
REM C:\Windows\System32\cmd.exe /A /Q /K C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\qtenv2.bat

REM SET QTDIR=C:\QtSDK\Desktop\Qt\4.8.1\mingw
SET QTDIR=C:\Qt\4.8.4

SET PATH=%QTDIR%\bin;%PATH%
SET PATH=%PATH%;C:\QtSDK\mingw\bin
REM SET PATH=%PATH%;D:\mingw\msys\1.0\open-egovernment\bin
REM SET PATH=%PATH%;D:\mingw\bin
SET PATH=%PATH%;%SystemRoot%\System32
SET QMAKESPEC=win32-g++

:: Setting D-Bus session and system bus addresses

SET DBUS_SESSION_BUS_ADDRESS=autolaunch:scope=install-path
SET DBUS_SYSTEM_BUS_DEFAULT_ADDRESS=nonce-tcp: 
REM SET DBUS_VERBOSE=1

