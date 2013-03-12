@ECHO OFF

REM $Id: copy-files.bat 410 2012-03-22 22:29:36Z gerrit-albrecht $

REM Copies the files needed for deployment into the OEG directory structure.
REM After this step it should be possible to use compiled OEG applications
REM without a MinGW/Qt (SDK) installation. Files not copied here must not be
REM required by an OEG application.

CD /D "%0"\..

REM Here you have to set the source paths from where you want to copy the files.
REM All copies go into the bin/lib/plugins respective bin64/lib64/plugins64 directories.

SET CLEANDIRS=NO
SET COPYQT5DIR=YES
SET COPYQT5MINGW32DIRS=NO
SET COPYQT5MINGW64DIRS=NO
SET COPYQT5FROMOWNDIR=NO

IF "%CLEANDIRS%" == "YES" CALL clean-dirs.bat

IF NOT EXIST bin (
  ECHO No bin directory found.
)
IF NOT EXIST bin64 (
  ECHO No bin64 directory found.
)
IF NOT EXIST plugins (
  ECHO No plugins directory found.
)
IF NOT EXIST plugins64 (
  ECHO No plugins64 directory found.
)

IF NOT "%COPYQT5DIR%" == "YES" GOTO NO_COPYQT5DIR
  ECHO Copying original files from Qt5 setup directory...
  ECHO Script tested with this Qt setup file:
  ECHO qt-windows-opensource-5.0.2-mingw47_32-x86-offline-2013-02-23-433.exe
  SET SRCDIR=C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin
  SET DSTDIR=bin
  ECHO Copying to "bin"
  ECHO S=%SRCDIR% D=%DSTDIR%

  COPY /B /Y "%SRCDIR%\D3DCompiler_43.dll"        "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\icudt49.dll"               "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\icuin49.dll"               "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\icuuc49.dll"               "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\libEGL.dll"                "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\libgcc_s_sjlj-1.dll"       "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\libGLESv2.dll"             "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\libstdc++-6.dll"           "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\libwinpthread-1.dll"       "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5CLucene.dll"            "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Concurrent.dll"         "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Core.dll"               "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5Declarative.dll"        "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5Designer.dll"           "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5DesignerComponents.dll" "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Gui.dll"                "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Help.dll"               "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Multimedia.dll"         "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5MultimediaQuick_p.dll"  "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5MultimediaWidgets.dll"  "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Network.dll"            "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5OpenGL.dll"             "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5PrintSupport.dll"       "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5Qml.dll"                "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5Quick.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5QuickParticles.dll"     "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5QuickTest.dll"          "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Script.dll"             "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5ScriptTools.dll"        "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Sql.dll"                "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Svg.dll"                "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\Qt5Test.dll"               "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5V8.dll"                 "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5WebKit.dll"             "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5WebKitWidgets.dll"      "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Widgets.dll"            "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5Xml.dll"                "%DSTDIR%"
  COPY /B /Y "%SRCDIR%\Qt5XmlPatterns.dll"        "%DSTDIR%"

  SET SRCDIR=C:\Qt\Qt5.0.2\5.0.2\mingw47_32\plugins
  SET DSTDIR=plugins
  ECHO Copying to "plugins"

  REM Copy all plugin files, without debug files or static libraries.

  XCOPY /E /H /Y "%SRCDIR%\accessible\qtaccessiblequick.dll"        "plugins\qt\accessible"
  XCOPY /E /H /Y "%SRCDIR%\accessible\qtaccessiblewidgets.dll"      "plugins\qt\accessible"
  XCOPY /E /H /Y "%SRCDIR%\bearer\qgenericbearer.dll"               "plugins\qt\bearer"
  XCOPY /E /H /Y "%SRCDIR%\bearer\qnativewifibearer.dll"            "plugins\qt\bearer"
  XCOPY /E /H /Y "%SRCDIR%\designer\qaxwidget.dll"                  "plugins\qt\designer"
  XCOPY /E /H /Y "%SRCDIR%\designer\qdeclarativeview.dll"           "plugins\qt\designer"
  XCOPY /E /H /Y "%SRCDIR%\designer\qwebview.dll"                   "plugins\qt\designer"
  XCOPY /E /H /Y "%SRCDIR%\iconengines\qsvgicon.dll"                "plugins\qt\iconengines"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qgif.dll"                   "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qico.dll"                   "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qjpeg.dll"                  "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qmng.dll"                   "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qsvg.dll"                   "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qtga.dll"                   "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qtiff.dll"                  "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\qwbmp.dll"                  "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\mediaservice\dsengine.dll"               "plugins\qt\mediaservice"
  XCOPY /E /H /Y "%SRCDIR%\mediaservice\qtmedia_audioengine.dll"    "plugins\qt\mediaservice"
  XCOPY /E /H /Y "%SRCDIR%\platforms\qminimal.dll"                  "plugins\qt\platforms"
  XCOPY /E /H /Y "%SRCDIR%\platforms\qwindows.dll"                  "plugins\qt\platforms"
  XCOPY /E /H /Y "%SRCDIR%\playlistformats\qtmultimedia_m3u.dll"    "plugins\qt\playlistformats"
  XCOPY /E /H /Y "%SRCDIR%\printsupport\windowsprintersupport.dll"  "plugins\qt\printsupport"
  XCOPY /E /H /Y "%SRCDIR%\qmltooling\qmldbg_inspector.dll"         "plugins\qt\qmltooling"
  XCOPY /E /H /Y "%SRCDIR%\qmltooling\qmldbg_qtquick2.dll"          "plugins\qt\qmltooling"
  XCOPY /E /H /Y "%SRCDIR%\qmltooling\qmldbg_tcp.dll"               "plugins\qt\qmltooling"
  XCOPY /E /H /Y "%SRCDIR%\qmltooling\qmldbg_tcp_qtdeclarative.dll" "plugins\qt\qmltooling"
  XCOPY /E /H /Y "%SRCDIR%\sqldrivers\qsqlite.dll"                  "plugins\qt\sqldrivers"
  XCOPY /E /H /Y "%SRCDIR%\sqldrivers\qsqlodbc.dll"                 "plugins\qt\sqldrivers"
:NO_COPYQT5DIR

IF "%COPYQT5MINGW32DIRS%" == "YES" (
  ECHO Copying files from mingwbuilds Qt5-32 and MinGW-32 directories...
  SET SRCDIR=E:\Qt32-5.0.1\bin
  SET DSTDIR=bin
  ECHO Copying to "bin"

REM COPY /B /Y "%SRCDIR%\Aggregation.dll"           "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\CPlusPlus.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\GLSL.dll"                  "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\icudt*50.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libbz2-1.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libcharset-1.dll"          "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libeay32.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libexpat-1.dll"            "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libexslt-0.dll"            "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libfontconfig-1.dll"       "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libfreetype-6.dll"         "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libgnurx-0.dll"            "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libhistory6.dll"           "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libiconv-2.dll"            "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\liblzma-5.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\liblzo2-2.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libpcre16-0.dll"           "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libpcre-1.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libpcrecpp-0.dll"          "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libpcreposix-0.dll"        "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libreadline6.dll"          "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libsqlite3-0.dll"          "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libxml2-2.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\libxslt-1.dll"             "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\ssleay32.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\zeroconf.dll"              "%DSTDIR%"
REM COPY /B /Y "%SRCDIR%\zlib1.dll"                 "%DSTDIR%"

  SET SRCDIR=E:\Qt32-5.0.1\plugins
  SET DSTDIR=plugins
  ECHO Copying to "plugins"

  REM Copy all plugin files, including debug files.

  XCOPY /E /H /Y "%SRCDIR%\accessible\*.dll"       "plugins\qt\accessible"
  XCOPY /E /H /Y "%SRCDIR%\bearer\*.dll"           "plugins\qt\bearer"
  XCOPY /E /H /Y "%SRCDIR%\designer\*.dll"         "plugins\qt\designer"
  XCOPY /E /H /Y "%SRCDIR%\iconengines\*.dll"      "plugins\qt\iconengines"
  XCOPY /E /H /Y "%SRCDIR%\imageformats\*.dll"     "plugins\qt\imageformats"
  XCOPY /E /H /Y "%SRCDIR%\mediaservice\*.dll"     "plugins\qt\mediaservice"
  XCOPY /E /H /Y "%SRCDIR%\platforms\*.dll"        "plugins\qt\platforms"
  XCOPY /E /H /Y "%SRCDIR%\playlistformats\*.dll"  "plugins\qt\playlistformats"
  XCOPY /E /H /Y "%SRCDIR%\printsupport\*.dll"     "plugins\qt\printsupport"
  XCOPY /E /H /Y "%SRCDIR%\qmltooling\*.dll"       "plugins\qt\qmltooling"
  XCOPY /E /H /Y "%SRCDIR%\sqldrivers\*.dll"       "plugins\qt\sqldrivers"
  XCOPY /E /H /Y "%SRCDIR%\webkit\*.dll"           "plugins\qt\webkit"
) ELSE (
  ECHO Skipping copy of Qt5-32/MinGW-32 files.
)

IF "%COPYQT5MINGW64DIRS%" == "YES" (
  ECHO Copying files from mingwbuilds Qt5-64 and MinGW-64 directories...
  SET SRCDIR=E:\Qt64-5.0.1\bin
  SET DSTDIR=bin64
  ECHO Copying to "bin64"


) ELSE (
  ECHO Skipping copy of Qt5-64/MinGW-64 files.
)

ECHO Check output for errors!
PAUSE

