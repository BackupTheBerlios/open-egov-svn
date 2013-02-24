@ECHO OFF

REM $Id:$

CD /D "%0"\..

SET SVNCMD="c:\Program Files\TortoiseSVN\bin\svn.exe"
SET SVNVERCMD="c:\Program Files\TortoiseSVN\bin\svnversion.exe"
SET OEGREPO="https://gerrit-albrecht@svn.berlios.de/svnroot/repos/open-egov/trunk/"

REM --xml --incremental -R
REM %SVNCMD% info %OEGREPO% -r HEAD --non-interactive

REM for /f %%i in ('dir /b /s XY*.exe') do ren "%%i" *.exe_old
REM Wenn du Leerzeichen im Pfad hast einfach "tokens=*" hinter /f stellen.

REM svnversion returns e.g. "123M" in case the sources are modified.
REM We only use the HEAD revision number without additional flags.
REM Don't use svn.exe, because it needs the -R flag and a lot of time.

FOR /f "delims=SM" %%a IN ('%%SVNVERCMD%% ..\..') DO @SET REVISION=%%a

ECHO Current revision: %REVISION%

REM We create the resulting XML file "revision.wxi" with this batch because it is simpler.
REM Alternatives could be: cscript xsltrans.js Revision.xml Revision.xsl
REM or: msxsl.exe Revision.xml Revision.xsl –o Revision.wxi currentRevision=%REVISION%

SET REVISIONFILENAME=Revision.wxi
IF EXIST Revision.wxi DEL Revision.wxi

ECHO ^<?xml version="1.0" encoding="UTF-8"?^>>>%REVISIONFILENAME%
ECHO.>>%REVISIONFILENAME%
ECHO ^<!-- Automatically created file. --^>>>%REVISIONFILENAME%
ECHO.>>%REVISIONFILENAME%
ECHO ^<Include xmlns='http://schemas.microsoft.com/wix/2006/wi'^>>>%REVISIONFILENAME%
ECHO   ^<!-- Revision is NOT used by WiX in the upgrade procedure --^>>>%REVISIONFILENAME%
ECHO   ^<?define Revision="%REVISION%" ?^>>>%REVISIONFILENAME%
ECHO ^</Include^>>>%REVISIONFILENAME%
ECHO.>>%REVISIONFILENAME%

