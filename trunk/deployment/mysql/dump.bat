@ECHO OFF

REM $Id$

CD /D "%0"\..

ECHO Dumping databases of the Open E-Government MySQL server.

DEL databases.sql

C:\MySQL\bin\mysqldump.exe --no-defaults --quick --all-databases --flush-privileges --opt --port=3306 --result-file=databases.sql

REM --user= password host port
REM --tab=/path/to/some/dir --opt --full
REM --databases

PAUSE

