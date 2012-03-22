@ECHO OFF

REM $Id$

REM Copies the files needed for deployment into the OEG directory structure.
REM After this step it should be possible to use the applications without
REM a MinGW/Qt (SDK) installation. Files not copied here must not be required
REM by an OEG application.
REM
REM For Qt SDK 1.2 (2012-02-01).

CD /D "%0"\..\bin

SET SRCDIR=C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin

COPY /B /Y "%SRCDIR%\libgcc_s_dw2-1.dll" .
COPY /B /Y "%SRCDIR%\mingwm10.dll" .
COPY /B /Y "%SRCDIR%\phonon4.dll" .
COPY /B /Y "%SRCDIR%\QtCLucene4.dll" .
COPY /B /Y "%SRCDIR%\QtCore4.dll" .
COPY /B /Y "%SRCDIR%\QtDeclarative4.dll" .
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

SET SRCDIR=C:\QtSDK\QtCreator\bin

COPY /B /Y "%SRCDIR%\QtConcurrent.dll" .
COPY /B /Y "%SRCDIR%\libeay32.dll" .
COPY /B /Y "%SRCDIR%\libssl32.dll" .
COPY /B /Y "%SRCDIR%\ssleay32.dll" .

SET SRCDIR=C:\QtSDK\mingw\bin

COPY /B /Y "%SRCDIR%\libstdc++-6.dll" .


CD /D "%0"\..

SET SRCDIR=C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins

IF EXIST plugins (
  ECHO The plugins directory already exists.
) ELSE (
  ECHO No plugins directory found. Creating.
  MD plugins
)
CD plugins

IF EXIST qt (
  ECHO The plugins/qt directory already exists.
) ELSE (
  ECHO No plugins/qt directory found. Creating.
  MD qt
)
CD qt

IF NOT EXIST accessible      MD accessible
IF NOT EXIST bearer          MD bearer
IF NOT EXIST codecs          MD codecs
IF NOT EXIST designer        MD designer
IF NOT EXIST graphicssystems MD graphicssystems
IF NOT EXIST iconengines     MD iconengines
IF NOT EXIST imageformats    MD imageformats
IF NOT EXIST phonon_backend  MD phonon_backend
IF NOT EXIST qmltooling      MD qmltooling
IF NOT EXIST sqldrivers      MD sqldrivers

REM Don't removing, only cleaning.

DEL accessible\*.DLL
DEL bearer\*.DLL
DEL codecs\*.DLL
DEL designer\*.DLL
DEL graphicssystems\*.DLL
DEL iconengines\*.DLL
DEL imageformats\*.DLL
DEL phonon_backend\*.DLL
DEL qmltooling\*.DLL
DEL sqldrivers\*.DLL

XCOPY /E /H /Y "%SRCDIR%\accessible"     accessible
XCOPY /E /H /Y "%SRCDIR%\codecs"         codecs
XCOPY /E /H /Y "%SRCDIR%\iconengines"    iconengines
XCOPY /E /H /Y "%SRCDIR%\imageformats"   imageformats
XCOPY /E /H /Y "%SRCDIR%\sqldrivers"     sqldrivers

XCOPY /E /H /Y "%SRCDIR%\bearer\qgenericbearer4.dll"                bearer
XCOPY /E /H /Y "%SRCDIR%\bearer\qnativewifibearer4.dll"             bearer
XCOPY /E /H /Y "%SRCDIR%\graphicssystems\qglgraphicssystem4.dll"    graphicssystems
XCOPY /E /H /Y "%SRCDIR%\graphicssystems\qtracegraphicssystem4.dll" graphicssystems
XCOPY /E /H /Y "%SRCDIR%\phonon_backend\phonon_ds94.dll"            phonon_backend

ECHO Check output for errors!
PAUSE

