@ECHO OFF

REM $Id$

REM Copies the files needed for deployment into the OEG directory structure.
REM After this step it should be possible to use the applications without
REM a MinGW/Qt (SDK) installation. Files not copied here must not be required
REM by an OEG application.

REM There are two dirs with Qt-DLLs containing different sized files, both
REM are no complete file sets (OpenGL, Concurrent, ...).
REM Also there are two places with plugins... Chaos.

CD /D "%0"\..\..\bin

SET SRCDIR=C:\Qt\4.7.0-beta1\bin
SET SRCDIR=C:\Qt\2010.04\qt\bin

COPY /B /Y "%SRCDIR%\mingwm10.dll" .
COPY /B /Y "%SRCDIR%\libgcc_s_dw2-1.dll" .

COPY /B /Y "%SRCDIR%\phonon4.dll" .
COPY /B /Y "%SRCDIR%\QtCore4.dll" .
COPY /B /Y "%SRCDIR%\QtGui4.dll" .
COPY /B /Y "%SRCDIR%\QtHelp4.dll" .
COPY /B /Y "%SRCDIR%\QtMultimedia4.dll" .
COPY /B /Y "%SRCDIR%\QtNetwork4.dll" .
COPY /B /Y "%SRCDIR%\QtOpenGL4.dll" .
COPY /B /Y "%SRCDIR%\QtScript4.dll" .
COPY /B /Y "%SRCDIR%\QtScriptTools4.dll" .
COPY /B /Y "%SRCDIR%\QtSql4.dll" .
COPY /B /Y "%SRCDIR%\QtSvg4.dll" .
COPY /B /Y "%SRCDIR%\QtWebKit4.dll" .
COPY /B /Y "%SRCDIR%\QtXml4.dll" .
COPY /B /Y "%SRCDIR%\QtXmlPatterns4.dll" .

SET SRCDIR=C:\Qt\2010.04\bin

COPY /B /Y "%SRCDIR%\QtConcurrent.dll" .

REM Oder nach "plugins" verschieben?

MD accessible
MD codecs
MD iconengines
MD imageformats
MD sqldrivers
XCOPY /E /H /Y "%SRCDIR%\accessible"   accessible
XCOPY /E /H /Y "%SRCDIR%\codecs"       codecs
XCOPY /E /H /Y "%SRCDIR%\iconengines"  iconengines
XCOPY /E /H /Y "%SRCDIR%\imageformats" imageformats
XCOPY /E /H /Y "%SRCDIR%\sqldrivers"   sqldrivers

REM SET SRCDIR=C:\MinGW\bin
SET SRCDIR=C:\Qt\2010.04\mingw\bin

COPY /B /Y "%SRCDIR%\mingwm10.dll" .
COPY /B /Y "%SRCDIR%\libstdc++-6.dll" .
COPY /B /Y "%SRCDIR%\libgcc_s_dw2-1.dll" .

ECHO Check output for errors!
PAUSE

