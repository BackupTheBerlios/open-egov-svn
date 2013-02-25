@ECHO OFF

REM $Id$

CD /D "%0"\..

CALL Revision.bat

SET PATH=%PATH%;C:\Program Files (x86)\WiX Toolset v3.7\bin;C:\Programme\Windows Installer XML v3.5\bin
SET CAPARA=-nologo -pedantic
SET LIPARA=-nologo -pedantic -sw1101 -ext WixUIExtension 

candle "Open E-Government - App - MudMania - 0.0.1.wxs"
light -ext WixUIExtension -ext WixUtilExtension -cultures:en-us -loc strings\en-us.wxl -b ..\.. "Open E-Government - App - MudMania - 0.0.1.wixobj"

REM msiexec /i product.msi

ECHO Finished. Check output for errors.
PAUSE

