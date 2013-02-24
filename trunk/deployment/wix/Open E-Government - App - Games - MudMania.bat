@ECHO OFF

REM $Id$

CD /D "%0"\..

SET PATH=%PATH%;C:\Program Files\WiX Toolset v3.7\bin;C:\Programme\Windows Installer XML v3.5\bin

candle "Open E-Government - App - MudMania - 0.0.1.wxs"
light -ext WixUIExtension -ext WixUtilExtension -cultures:en-us -loc strings\en-us.wxl -b ..\.. "Open E-Government - App - MudMania - 0.0.1.wixobj"

REM msiexec /i product.msi

ECHO Finished. Check output for errors.
PAUSE

