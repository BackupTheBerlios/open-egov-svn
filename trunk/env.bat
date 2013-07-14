@ECHO OFF

REM $Id$

SET USEQT5=YES
SET USEMINGW32QT32=NO
SET USEMINGW64QT64=NO

REM Redirect temporary directory. Needed if you want to work from a (slow)
REM USB stick and store intermediate temporary files on the hard or a ram disk.

IF NOT EXIST C:\temp\NUL GOTO NO_C_DRIVE
ECHO TEMP=C:\temp
SET TEMP=C:\temp
SET TMP=C:\temp
GOTO TEMP_FOUND
:NO_C_DRIVE

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


REM Setting up environment for Qt usage...
REM Look into qtenv2.bat for updated data.
REM C:\Windows\System32\cmd.exe /A /Q /K C:\Qt\Qt5.1.0\5.1.0\mingw48_32\bin\qtenv2.bat

IF NOT "%USEQT5%" == "YES" GOTO NO_USEQT5
  ECHO Using standard Qt5 setup directory...
  IF EXIST C:\Qt\Qt5.1.0\5.1.0\mingw48_32\nul SET QTDIR=C:\Qt\Qt5.1.0\5.1.0\mingw48_32
  SET PATH=%QTDIR%\bin;C:\Qt\Qt5.1.0\Tools\mingw48_32\bin;%PATH%
  SET EXAMPLESDIR=%QTDIR%\examples
  GOTO QTDIR_FOUND_PATH_SET
:NO_USEQT5

IF NOT "%USEMINGW32QT32%" == "YES" GOTO NO_USEMINGW32QT32
  ECHO Using MinGW-32 and Qt5-32...
  IF EXIST C:\Qt32-5.0.1 SET QTDIR=C:\Qt32-5.0.1
  IF EXIST D:\Qt32-5.0.1 SET QTDIR=D:\Qt32-5.0.1
  IF EXIST E:\Qt32-5.0.1 SET QTDIR=E:\Qt32-5.0.1
  IF EXIST C:\mingw32    SET MINGWDIR=C:\mingw32
  IF EXIST D:\mingw32    SET MINGWDIR=D:\mingw32
  IF EXIST E:\mingw32    SET MINGWDIR=E:\mingw32
  SET PATH=%MINGWDIR%\bin;%QTDIR%\bin;%PATH%
  GOTO QTDIR_FOUND_PATH_SET
:NO_USEMINGW32QT32

REM IF "%USEMINGW32QT32%" == "YES" (
REM  ECHO Using MinGW-32 and Qt5-32...
REM  REM Warum funktioniert das nicht, aber den Pfad direkt reinschreiben geht?
REM  SET QTDIR=E:\Qt32-5.0.1
REM  REM SET PATH=E:\mingw32\bin;%QTDIR%\bin;%PATH%
REM  SET PATH=E:\mingw32\bin;E:\Qt32-5.0.1\bin;%PATH%
REM )

IF "%USEMINGW64QT64%" == "YES" (
  ECHO Using MinGW-64 and Qt5-64...
  IF EXIST C:\Qt64-5.0.1 SET QTDIR=C:\Qt64-5.0.1
  IF EXIST D:\Qt64-5.0.1 SET QTDIR=D:\Qt64-5.0.1
  IF EXIST E:\Qt64-5.0.1 SET QTDIR=E:\Qt64-5.0.1
  IF EXIST C:\mingw64    SET MINGWDIR=C:\mingw64
  IF EXIST D:\mingw64    SET MINGWDIR=D:\mingw64
  IF EXIST E:\mingw64    SET MINGWDIR=E:\mingw64
  SET PATH=%MINGWDIR%\bin;%QTDIR%\bin;%PATH%
  GOTO QTDIR_FOUND_PATH_SET
)

:QTDIR_FOUND_PATH_SET

REM SET QMAKESPEC=win32-g++
REM SET PATH=%PATH%;E:\msys\bin
SET PATH=%PATH%;%SystemRoot%\System32

:: Setting D-Bus session and system bus addresses

SET DBUS_SESSION_BUS_ADDRESS=autolaunch:scope=install-path
SET DBUS_SYSTEM_BUS_DEFAULT_ADDRESS=nonce-tcp: 
REM SET DBUS_VERBOSE=1

