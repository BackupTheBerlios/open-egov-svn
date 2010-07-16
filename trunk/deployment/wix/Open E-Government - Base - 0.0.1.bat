@ECHO OFF

REM $Id$

CD /D "%0"\..

SET PATH=%PATH%;C:\Programme\Windows Installer XML v3.5\bin

candle "Open E-Government - Base - 0.0.1.wxs"
light  "Open E-Government - Base - 0.0.1.wixobj"

REM msiexec /i product.msi

ECHO Finished. Check output for errors.
PAUSE

