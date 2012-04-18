@ECHO OFF

REM $Id:$

REM Look into C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\qtenv2.bat for updated data.
REM C:\Windows\System32\cmd.exe /A /Q /K C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\qtenv2.bat

set QTDIR=C:\QtSDK\Desktop\Qt\4.8.1\mingw
set PATH=%QTDIR%\bin;%PATH%;%SystemRoot%\System32
set PATH=C:\QtSDK\mingw\bin;%PATH%
set QMAKESPEC=win32-g++


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

