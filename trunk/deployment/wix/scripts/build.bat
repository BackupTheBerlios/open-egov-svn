@ECHO OFF

REM $Id$

IF NOT EXIST installers MD installers

COPY base.msi installers/base-en.msi

CALL embed.bat base de 1031

REM CALL embed.bat base da 1030
REM CALL embed.bat base es 1034
REM CALL embed.bat base fi 1035
REM CALL embed.bat base fr 1036
REM CALL embed.bat base it 1040
REM CALL embed.bat base jp 1041
REM CALL embed.bat base ko 1042
REM CALL embed.bat base nl 1043
REM CALL embed.bat base no 1044
REM CALL embed.bat base pt_br 1046
REM CALL embed.bat base sv 1053
REM CALL embed.bat base zh_cn 2052
REM CALL embed.bat base zh_tw 1028
REM CALL embed.bat base ru 1049
REM CALL embed.bat base tr 1055
REM CALL embed.bat base pl 1045
REM CALL embed.bat base pt_pt 2070
