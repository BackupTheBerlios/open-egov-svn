@ECHO OFF

REM $Id$

SET filename=%1
SET langname=%2
SET langcode=%3

SET PATH=%PATH%;C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin;C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin\

COPY %filename%_en.msi %filename%_%langname%.msi

cscript WiLangId.vbs %filename%_%langname%.msi Product %langcode% > embed_%langname%.txt
MsiTran.exe -g %filename%_en.msi %filename%_%langname%.msi %langname%.mst >> embed_%langname%.txt
cscript wisubstg.vbs %filename%_en.msi %langname%.mst %langcode% >> embed_%langname%.txt
cscript wisubstg.vbs %filename%_en.msi >> embed_%langname%.txt

