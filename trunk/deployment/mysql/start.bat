@ECHO OFF

REM $Id$

CD /D "%0"\..

ECHO Starting MySQL server with Open E-Government configuration.
ECHO Stop with Ctrl+C.

REM COPY my.ini C:\MySQL\my.ini

C:\MySQL\bin\mysqld.exe --standalone --console --datadir=C:/MySQL/open-egovernment-data --port=3306 --max_connections=25

PAUSE

