@ECHO OFF

rem $Id$

rem Copies the files needed for deployment into the OEG directory structure.
rem After this step it should be possible to use the applications without
rem a MinGW/Qt (SDK) installation. Files not copied here must not be required
rem by an OEG application.

SET SRCDIR=C:\Qt\4.7.0-beta1\bin
CD /D "%0"\..\..\bin

COPY /B /Y "%SRCDIR%\mingwm10.dll" .
COPY /B /Y "%SRCDIR%\phonon4.dll" .
COPY /B /Y "%SRCDIR%\QtCore4.dll" .
COPY /B /Y "%SRCDIR%\QtGui4.dll" .
COPY /B /Y "%SRCDIR%\QtNetwork4.dll" .
COPY /B /Y "%SRCDIR%\QtOpenGL4.dll" .
COPY /B /Y "%SRCDIR%\QtScript4.dll" .
COPY /B /Y "%SRCDIR%\QtSql4.dll" .
COPY /B /Y "%SRCDIR%\QtSvg4.dll" .

ECHO Check output for errors!
PAUSE

