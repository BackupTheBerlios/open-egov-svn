@ECHO OFF

REM $Id$

REM First we generate with candle the .wixobj file.
REM Every language needs to be translated using the right codepage. 1252 is for en and de.
REM Table of CodePages: http://www.tramontana.co.hu/wix/lesson2.php#2.4
REM Then light links the .wixobj and generates the .wixpdb and then .msi files.
REM You can switch off warnings using -swXXXX.
REM Warning 1101: DefaultLanguage used because no VERSION_INFO block in file.
REM Test the installer with: msiexec /i product.msi

CD /D "%0"\..

SET PATH=%PATH%;C:\Programme\WiX Toolset v3.7\;C:\Programme\Windows Installer XML v3.5\bin
SET CAPARA=-nologo -pedantic
SET LIPARA=-nologo -pedantic -sw1101 -ext WixUIExtension 

candle %CAPARA% -dCodepage=1252 -dLicense=license.en.rtf "Open E-Government - Base.wxs"
light %LIPARA% -cultures:en-us -loc strings\en-us.wxl -out en-us.msi "Open E-Government - Base.wixobj"
candle %CAPARA% -dCodepage=1252 -dLicense=license.de.rtf "Open E-Government - Base.wxs"
light %LIPARA% -cultures:de-de -loc strings\de-de.wxl -out de-de.msi "Open E-Government - Base.wixobj"

DEL de-de.wixpdb en-us.wixpdb

torch.exe -p -t language en-us.msi de-de.msi -out de-de.mst
COPY en-us.msi new.msi
cscript.exe scripts\WiSubStg.vbs new.msi de-de.mst 1031
cscript.exe scripts\WiLangId.vbs new.msi Package 1033,1031

MOVE new.msi "Open E-Government - Base.msi"

DEL de-de.mst de-de.msi en-us.msi

ECHO Finished. Check output for errors.
PAUSE

