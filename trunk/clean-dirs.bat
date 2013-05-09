@ECHO OFF

REM $Id$

REM Script which is needed by the copy-files.bat script.
REM It removes all (!) files from the official setup directories
REM and creates the correct directory structure for creating or
REM copying new files into it.

REM All copied files go to the bin/lib/plugins respective the
REM bin64/lib64/plugins64 directories.
REM This script cleans only bin and plugins, not the lib directories.

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
REM codecs, graphicssystems, phonon_backend, webkit added.

IF NOT EXIST plugins                      MD plugins
IF NOT EXIST plugins\qt                   MD plugins\qt
IF NOT EXIST plugins\qt\codecs            MD plugins\qt\codecs
IF NOT EXIST plugins\qt\graphicssystems   MD plugins\qt\graphicssystems
IF NOT EXIST plugins\qt\phonon_backend    MD plugins\qt\phonon_backend
IF NOT EXIST plugins\qt\accessible        MD plugins\qt\accessible
IF NOT EXIST plugins\qt\bearer            MD plugins\qt\bearer
IF NOT EXIST plugins\qt\designer          MD plugins\qt\designer
IF NOT EXIST plugins\qt\iconengines       MD plugins\qt\iconengines
IF NOT EXIST plugins\qt\imageformats      MD plugins\qt\imageformats
IF NOT EXIST plugins\qt\mediaservice      MD plugins\qt\mediaservice
IF NOT EXIST plugins\qt\platforms         MD plugins\qt\platforms
IF NOT EXIST plugins\qt\playlistformats   MD plugins\qt\playlistformats
IF NOT EXIST plugins\qt\printsupport      MD plugins\qt\printsupport
IF NOT EXIST plugins\qt\qmltooling        MD plugins\qt\qmltooling
IF NOT EXIST plugins\qt\sqldrivers        MD plugins\qt\sqldrivers
IF NOT EXIST plugins\qt\webkit            MD plugins\qt\webkit

IF NOT EXIST plugins64                    MD plugins64
IF NOT EXIST plugins64\qt                 MD plugins64\qt
IF NOT EXIST plugins64\qt\codecs          MD plugins64\qt\codecs
IF NOT EXIST plugins64\qt\graphicssystems MD plugins64\qt\graphicssystems
IF NOT EXIST plugins64\qt\phonon_backend  MD plugins64\qt\phonon_backend
IF NOT EXIST plugins64\qt\accessible      MD plugins64\qt\accessible
IF NOT EXIST plugins64\qt\bearer          MD plugins64\qt\bearer
IF NOT EXIST plugins64\qt\designer        MD plugins64\qt\designer
IF NOT EXIST plugins64\qt\iconengines     MD plugins64\qt\iconengines
IF NOT EXIST plugins64\qt\imageformats    MD plugins64\qt\imageformats
IF NOT EXIST plugins64\qt\mediaservice    MD plugins64\qt\mediaservice
IF NOT EXIST plugins64\qt\platforms       MD plugins64\qt\platforms
IF NOT EXIST plugins64\qt\playlistformats MD plugins64\qt\playlistformats
IF NOT EXIST plugins64\qt\printsupport    MD plugins64\qt\printsupport
IF NOT EXIST plugins64\qt\qmltooling      MD plugins64\qt\qmltooling
IF NOT EXIST plugins64\qt\sqldrivers      MD plugins64\qt\sqldrivers
IF NOT EXIST plugins64\qt\webkit          MD plugins64\qt\webkit

REM Clean the directories.

IF EXIST plugins\qt\codecs            DEL plugins\qt\codecs\*.DLL
IF EXIST plugins\qt\graphicssystems   DEL plugins\qt\graphicssystems\*.DLL
IF EXIST plugins\qt\phonon_backend    DEL plugins\qt\phonon_backend\*.DLL
IF EXIST plugins\qt\accessible        DEL plugins\qt\accessible\*.DLL
IF EXIST plugins\qt\bearer            DEL plugins\qt\bearer\*.DLL
IF EXIST plugins\qt\designer          DEL plugins\qt\designer\*.DLL
IF EXIST plugins\qt\iconengines       DEL plugins\qt\iconengines\*.DLL
IF EXIST plugins\qt\imageformats      DEL plugins\qt\imageformats\*.DLL
IF EXIST plugins\qt\mediaservice      DEL plugins\qt\mediaservice\*.DLL
IF EXIST plugins\qt\platforms         DEL plugins\qt\platforms\*.DLL
IF EXIST plugins\qt\playlistformats   DEL plugins\qt\playlistformats\*.DLL
IF EXIST plugins\qt\printsupport      DEL plugins\qt\printsupport\*.DLL
IF EXIST plugins\qt\qmltooling        DEL plugins\qt\qmltooling\*.DLL
IF EXIST plugins\qt\sqldrivers        DEL plugins\qt\sqldrivers\*.DLL
IF EXIST plugins\qt\webkit            DEL plugins\qt\webkit\*.DLL

IF EXIST plugins\qt\codecs            DEL plugins\qt\codecs\*.A
IF EXIST plugins\qt\graphicssystems   DEL plugins\qt\graphicssystems\*.A
IF EXIST plugins\qt\phonon_backend    DEL plugins\qt\phonon_backend\*.A
IF EXIST plugins\qt\accessible        DEL plugins\qt\accessible\*.A
IF EXIST plugins\qt\bearer            DEL plugins\qt\bearer\*.A
IF EXIST plugins\qt\designer          DEL plugins\qt\designer\*.A
IF EXIST plugins\qt\iconengines       DEL plugins\qt\iconengines\*.A
IF EXIST plugins\qt\imageformats      DEL plugins\qt\imageformats\*.A
IF EXIST plugins\qt\mediaservice      DEL plugins\qt\mediaservice\*.A
IF EXIST plugins\qt\platforms         DEL plugins\qt\platforms\*.A
IF EXIST plugins\qt\playlistformats   DEL plugins\qt\playlistformats\*.A
IF EXIST plugins\qt\printsupport      DEL plugins\qt\printsupport\*.A
IF EXIST plugins\qt\qmltooling        DEL plugins\qt\qmltooling\*.A
IF EXIST plugins\qt\sqldrivers        DEL plugins\qt\sqldrivers\*.A
IF EXIST plugins\qt\webkit            DEL plugins\qt\webkit\*.A

IF EXIST plugins64\qt\codecs          DEL plugins64\qt\codecs\*.DLL
IF EXIST plugins64\qt\graphicssystems DEL plugins64\qt\graphicssystems\*.DLL
IF EXIST plugins64\qt\phonon_backend  DEL plugins64\qt\phonon_backend\*.DLL
IF EXIST plugins64\qt\accessible      DEL plugins64\qt\accessible\*.DLL
IF EXIST plugins64\qt\bearer          DEL plugins64\qt\bearer\*.DLL
IF EXIST plugins64\qt\designer        DEL plugins64\qt\designer\*.DLL
IF EXIST plugins64\qt\iconengines     DEL plugins64\qt\iconengines\*.DLL
IF EXIST plugins64\qt\imageformats    DEL plugins64\qt\imageformats\*.DLL
IF EXIST plugins64\qt\mediaservice    DEL plugins64\qt\mediaservice\*.DLL
IF EXIST plugins64\qt\platforms       DEL plugins64\qt\platforms\*.DLL
IF EXIST plugins64\qt\playlistformats DEL plugins64\qt\playlistformats\*.DLL
IF EXIST plugins64\qt\printsupport    DEL plugins64\qt\printsupport\*.DLL
IF EXIST plugins64\qt\qmltooling      DEL plugins64\qt\qmltooling\*.DLL
IF EXIST plugins64\qt\sqldrivers      DEL plugins64\qt\sqldrivers\*.DLL
IF EXIST plugins64\qt\webkit          DEL plugins64\qt\webkit\*.DLL

IF EXIST plugins64\qt\codecs          DEL plugins64\qt\codecs\*.A
IF EXIST plugins64\qt\graphicssystems DEL plugins64\qt\graphicssystems\*.A
IF EXIST plugins64\qt\phonon_backend  DEL plugins64\qt\phonon_backend\*.A
IF EXIST plugins64\qt\accessible      DEL plugins64\qt\accessible\*.A
IF EXIST plugins64\qt\bearer          DEL plugins64\qt\bearer\*.A
IF EXIST plugins64\qt\designer        DEL plugins64\qt\designer\*.A
IF EXIST plugins64\qt\iconengines     DEL plugins64\qt\iconengines\*.A
IF EXIST plugins64\qt\imageformats    DEL plugins64\qt\imageformats\*.A
IF EXIST plugins64\qt\mediaservice    DEL plugins64\qt\mediaservice\*.A
IF EXIST plugins64\qt\platforms       DEL plugins64\qt\platforms\*.A
IF EXIST plugins64\qt\playlistformats DEL plugins64\qt\playlistformats\*.A
IF EXIST plugins64\qt\printsupport    DEL plugins64\qt\printsupport\*.A
IF EXIST plugins64\qt\qmltooling      DEL plugins64\qt\qmltooling\*.A
IF EXIST plugins64\qt\sqldrivers      DEL plugins64\qt\sqldrivers\*.A
IF EXIST plugins64\qt\webkit          DEL plugins64\qt\webkit\*.A

ECHO Check output for errors!
PAUSE

