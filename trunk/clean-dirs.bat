@ECHO OFF

REM $Id$

REM Script which is needed by the copy-files.bat script.
REM It removes all (!) files from the official setup directories
REM and creates the correct directory structure for creating or
REM copying new files into it.
REM
REM All cleaned and later (other script) copied files belong to
REM the bin/lib/plugins respective the bin64/lib64/plugins64
REM directories. Don't forget to rebuild or reinstall needed
REM additional libraries and tools which also are required
REM (e.g. gettext).

CD /D "%0"\..

IF NOT EXIST bin (
  ECHO No bin directory found. Creating it.
  MD bin
)

IF NOT EXIST bin64 (
  ECHO No bin64 directory found. Creating it.
  MD bin64
)

DEL "bin/*.a"
DEL "bin/*.exe"
DEL "bin/*.dll"

DEL "bin64/*.a"
DEL "bin64/*.exe"
DEL "bin64/*.dll"

IF EXIST plugins (
  ECHO The plugins directory already exists.
) ELSE (
  ECHO No plugins directory found. Creating it.
)

IF EXIST plugins64 (
  ECHO The plugins64 directory already exists.
) ELSE (
  ECHO No plugins64 directory found. Creating it.
)

REM Create directories, if missing.

IF NOT EXIST plugins                      MD plugins
IF NOT EXIST plugins\qt                   MD plugins\qt
IF NOT EXIST plugins\qt\accessible        MD plugins\qt\accessible
IF NOT EXIST plugins\qt\bearer            MD plugins\qt\bearer
IF NOT EXIST plugins\qt\designer          MD plugins\qt\designer
IF NOT EXIST plugins\qt\iconengines       MD plugins\qt\iconengines
IF NOT EXIST plugins\qt\imageformats      MD plugins\qt\imageformats
IF NOT EXIST plugins\qt\mediaservice      MD plugins\qt\mediaservice
IF NOT EXIST plugins\qt\platforms         MD plugins\qt\platforms
IF NOT EXIST plugins\qt\playlistformats   MD plugins\qt\playlistformats
IF NOT EXIST plugins\qt\printsupport      MD plugins\qt\printsupport
IF NOT EXIST plugins\qt\qml1tooling       MD plugins\qt\qml1tooling
IF NOT EXIST plugins\qt\qmltooling        MD plugins\qt\qmltooling
IF NOT EXIST plugins\qt\sensorgestures    MD plugins\qt\sensorgestures
IF NOT EXIST plugins\qt\sensors           MD plugins\qt\sensors
IF NOT EXIST plugins\qt\sqldrivers        MD plugins\qt\sqldrivers

IF NOT EXIST plugins64                    MD plugins64
IF NOT EXIST plugins64\qt                 MD plugins64\qt
IF NOT EXIST plugins64\qt\accessible      MD plugins64\qt\accessible
IF NOT EXIST plugins64\qt\bearer          MD plugins64\qt\bearer
IF NOT EXIST plugins64\qt\designer        MD plugins64\qt\designer
IF NOT EXIST plugins64\qt\iconengines     MD plugins64\qt\iconengines
IF NOT EXIST plugins64\qt\imageformats    MD plugins64\qt\imageformats
IF NOT EXIST plugins64\qt\mediaservice    MD plugins64\qt\mediaservice
IF NOT EXIST plugins64\qt\platforms       MD plugins64\qt\platforms
IF NOT EXIST plugins64\qt\playlistformats MD plugins64\qt\playlistformats
IF NOT EXIST plugins64\qt\printsupport    MD plugins64\qt\printsupport
IF NOT EXIST plugins64\qt\qml1tooling     MD plugins64\qt\qml1tooling
IF NOT EXIST plugins64\qt\qmltooling      MD plugins64\qt\qmltooling
IF NOT EXIST plugins64\qt\sensorgestures  MD plugins64\qt\sensorgestures
IF NOT EXIST plugins64\qt\sensors         MD plugins64\qt\sensors
IF NOT EXIST plugins64\qt\sqldrivers      MD plugins64\qt\sqldrivers

REM Clean the directories.

ECHO Deleting all files in plugins[64]\qt\ ...
FOR /F "tokens=* delims=" %%i IN ('DIR plugins\qt plugins64\qt /S /B /A:-D') DO (DEL "%%i")

REM TODO: Delete all files from plugins[64]\xyz (!qt)

ECHO Check output for errors!
PAUSE

