@ECHO OFF

REM $Id$

CD /D %0\..
CD

..\bin\createdatabase.exe --verbose currencies.xml
..\bin\createdatabase.exe --verbose dictionary.xml
..\bin\createdatabase.exe --verbose government.xml
..\bin\createdatabase.exe --verbose identities.xml
..\bin\createdatabase.exe --verbose iso-codes.xml
..\bin\createdatabase.exe --verbose nuts.xml
..\bin\createdatabase.exe --verbose organisms.xml
..\bin\createdatabase.exe --verbose people.xml
..\bin\createdatabase.exe --verbose places.xml
..\bin\createdatabase.exe --verbose products.xml
..\bin\createdatabase.exe --verbose users.xml

PAUSE

