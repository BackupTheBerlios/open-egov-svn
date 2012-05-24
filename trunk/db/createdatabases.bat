@ECHO OFF

REM $Id$

CD /D %0\..
CD

..\bin\createdatabase.exe dictionary.xml
..\bin\createdatabase.exe identities.xml
..\bin\createdatabase.exe iso-codes.xml
..\bin\createdatabase.exe organisms.xml
..\bin\createdatabase.exe people.xml
..\bin\createdatabase.exe places.xml
..\bin\createdatabase.exe products.xml
..\bin\createdatabase.exe users.xml

PAUSE

