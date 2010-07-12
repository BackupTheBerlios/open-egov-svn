# $Id$

TEMPLATE  = lib
CONFIG   += qt warn_on release
QT       += core
DESTDIR   = ../../../../bin

# $$OUT_PWD contains the directory of our .pro file with slashes
# like: C:/Test/123. Windows dislikes such paths. We could use
# "DESTDIR = ../../../../bin" but relative paths depend on the file
# (pro/pri) where they are noted. An absolute path is needed to
# call peflags from the bin directory. It is build using OUT_PWD
# but with correct slashes/backslashes. The target name is
# hard-coded (version number). Need a better solution...

win32 {
  BINDIR  = $${OUT_PWD}/$${DESTDIR}
  contains(DIR_SEPARATOR, "\\") {
    BINDIR = $$replace(BINDIR, "/", "\\")
  }
  PEFLAGS = $${BINDIR}$${DIR_SEPARATOR}peflags.exe
  exists($${PEFLAGS}) {
    QMAKE_POST_LINK = \"$${PEFLAGS}\" --dynamicbase=true --nxcompat=true \"$${BINDIR}$${DIR_SEPARATOR}$${TARGET}1.dll\"
  }
  else {
    warning("No peflags.exe found.")
  }
}

