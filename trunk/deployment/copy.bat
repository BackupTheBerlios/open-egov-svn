@echo off

rem $Id$

rem Copies the files needed for deployment into the OEG directory structure.
rem After this step it should be possible to use the applications without
rem a MinGW/Qt (SDK) installation. Files not copied here must not be required
rem by an OEG application.

SET BASE=D:\Projekte\berlios\open-egov
CD /D C:\Qt\4.7.0-beta1\bin

COPY /B /Y mingwm10.dll   "%BASE%\bin"
COPY /B /Y phonon4.dll    "%BASE%\bin"
COPY /B /Y QtCore4.dll    "%BASE%\bin"
COPY /B /Y QtGui4.dll     "%BASE%\bin"
COPY /B /Y QtNetwork4.dll "%BASE%\bin"
COPY /B /Y QtOpenGL4.dll  "%BASE%\bin"
COPY /B /Y QtScript4.dll  "%BASE%\bin"
COPY /B /Y QtSql4.dll     "%BASE%\bin"
COPY /B /Y QtSvg4.dll     "%BASE%\bin"

PAUSE

