# $Id$
#
# This file contains functions to help while building required packages
# without pre-built archives or the builder application. It is needed
# e.g. if the compiler changed or was updated and the builder is unable
# to build new OSS library binaries because the existing binary archives
# are incompatible with the current tools.
#
# Run a MSYS shell and source this file!

function oegdebug {
  if [ ! $# == 1 ]; then
    echo "Usage: oegdebug <1 or 0>"
    return
  fi

  export OEG_DEBUG="$1"
}

function oegmingwpath {
  if [ ! $# == 1 ]; then
    echo "Usage: oegmingwpath <32 or 64 bits as number>"
    return
  fi

  if [ "$1" = "32" ]; then
    export PATH=/d/dev/mingw32/bin:/d/dev/Qt-5.2.0-i686/bin:$PATH
  elif [ "$1" = "64" ]; then
    export PATH=/d/dev/mingw64/bin:/d/dev/Qt-5.2.0-x86_64/bin:$PATH
  else
    echo Wrong parameter: $1
    return
  fi
}

function oegenv {
  if [ ! $# == 1 ]; then
    echo "Usage: oegenv <32 or 64 bits as number>"  # not $0
    return   # don’t use exit!
  fi

  export OEG_BASE_DIR="/open-egovernment"
  export OEG_INSTALL_DIR="/open-egovernment-install"
  export OEG_WORK_DIR="/work"
  export OEG_PROJECT_DIR="/i/Projekte/open-egov"
  export OEG_DOWNLOADS_DIR="${OEG_PROJECT_DIR}/data/builder/downloads"
  export OEG_PATCHES_DIR="${OEG_PROJECT_DIR}/data/builder/patches"

  export LINGUAS="en de ar"
  export LANG=de

  #export OEG_PATH_TO_7ZIP="/c/Programme/7-Zip/7z.exe"
  export OEG_PATH_TO_7ZIP="/c/Program Files/7-Zip/7z.exe"

  #export OEG_ARCHIVE_FORMAT="zip"
  export OEG_ARCHIVE_FORMAT="7z"

  # When installing to $OEG_INSTALL_DIR: Do we want a "make install" or "make install-strip"?
  export OEG_CFG_MAKE_INSTALL_STRIP="yes"

  # Should oegarchive remove or update the target archive if there already exists one?
  export OEG_CFG_REMOVE_BINARY_ARCHIVE="yes"

  # -fomit-frame-pointer?
  local STDCFLAGS="-pipe -Wall -O2 -mms-bitfields"

  if [ "$1" = "32" ]; then
    export TARGETBITS="32"
    export OEG_BASE_BIN_DIR="${OEG_BASE_DIR}/bin"
    export OEG_BASE_LIB_DIR="${OEG_BASE_DIR}/lib"
    export CFLAGS="-m${TARGETBITS} -march=i686 -mtune=i686 $STDCFLAGS"
    export LDFLAGS="-m${TARGETBITS} -pipe -L${OEG_BASE_LIB_DIR}"
    export CONFIGURE_HOST_PARA="--host=i686-w64-mingw32"
    export PKG_CONFIG_PATH="${OEG_BASE_DIR}/lib/pkgconfig"
  elif [ "$1" = "64" ]; then
    export TARGETBITS="64"
    export OEG_BASE_BIN_DIR="${OEG_BASE_DIR}/bin64"
    export OEG_BASE_LIB_DIR="${OEG_BASE_DIR}/lib64"
    export CFLAGS="-m${TARGETBITS} -march=nocona -mtune=core2 $STDCFLAGS"
    export LDFLAGS="-m${TARGETBITS} -pipe -L${OEG_BASE_LIB_DIR}"
    export CONFIGURE_HOST_PARA="--host=x86_64-w64-mingw32"
    export PKG_CONFIG_PATH="${OEG_BASE_DIR}/lib${TARGETBITS}/pkgconfig"
  else
    echo Wrong parameter: $1
    return
  fi

  export CVS_RSH=ssh
  export PATH="${OEG_BASE_BIN_DIR}:${PATH}"

  export CXXFLAGS="$CFLAGS"
  export CPPFLAGS="-I${OEG_BASE_DIR}/include"

  export OEG_ARCHIVES_DIR="${OEG_PROJECT_DIR}/data/builder/archives/windows-${TARGETBITS}"
}

function oegpatch {
  if [ ! $# == 1 ]; then
    echo "Usage: oegarchive <number of patch file>"
    return
  fi

  #create: diff -Naur src src.neu > patch.txt
  #apply: patch --dry-run -p0 < patch.txt

  patch -p0 < ${OEG_PATCHES_DIR}/${PACKAGE_NAME}/${PACKAGE_NAME}-${PACKAGE_VERSION}-$1.txt
}

function oegarchive {
  if [ ! $# == 1 ]; then
    echo "Usage: oegarchive \"name-version\""
    return
  fi

  if [ "$1" = "" ]; then
    echo "Error: name was empty"
    return
  fi

  if [ "$TARGETBITS" = "" ]; then
    echo "Error: unknown target platform (32 or 64 bits?), call oegenv()"
    return
  fi

  if [ "$OEG_ARCHIVE_FORMAT" = "" ]; then
    echo "Error: unknown archive format, call oegenv()"
    return
  fi

  local ARCHIVEFILENAME="${OEG_ARCHIVES_DIR}/$1"

  cd "${OEG_INSTALL_DIR}/open-egovernment"

  if [ -f "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" ]; then
    if [ "$OEG_CFG_REMOVE_BINARY_ARCHIVE" = "yes" ]; then
      echo Error: The target file already existed and was deleted!
      rm -rf "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}"
    fi
  fi

  # Insert text files about the OEG project and the required dependencies here.

  case "${OEG_ARCHIVE_FORMAT}" in
    '7z')
      echo "Creating a 7-zip binary archive ..."
      "$OEG_PATH_TO_7ZIP" a -mx9 -t7z -ms -mmt -w.. "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" .
      ;;
    'zip')
      echo "Creating a zip binary archive ..."
      "$OEG_PATH_TO_7ZIP" a -tzip -w.. "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" .
      ;;
    *)
      echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
      echo "Error: No archive created!"
      return
      ;;
  esac

  cd ${OEG_WORK_DIR}
}

function oegcleaninstalldir {
  cd ${OEG_WORK_DIR}
  
  rm -rf ${OEG_INSTALL_DIR}
  mkdir ${OEG_INSTALL_DIR}
}

function oegcleanbasedir {
  cd ${OEG_WORK_DIR}

  rm -rf ${OEG_BASE_DIR}
  mkdir ${OEG_BASE_DIR}
}

function oeg_clean_work_dir {
  cd /
  rm -rf ${OEG_WORK_DIR}
  mkdir ${OEG_WORK_DIR}
  cd ${OEG_WORK_DIR}
}

function oegcleanbase {
  oegcleanbasedir
  oegcleaninstalldir
}

function formatversion {
  echo "$@" | awk -F. '{ printf("%d%03d%03d%03d\n", $1, $2, $3, $4); }';
}

function compareversions {
  if [[ $1 == $2 ]]; then
    return 0
  fi

  local paraX=$(formatversion $1)
  local paraY=$(formatversion $2)

  if [ $paraX == $paraY ]; then
    return 0
  fi

  if [ $paraX -gt $paraY ]; then
    return 1
  else
    return 2
  fi
}

function compareversionstext {
  compareversions $1 $2
  case $? in
        0) echo "eq";;
        1) echo "gt";;
        2) echo "lt";;
  esac
}

function oeg_get_extension {
  if [[ $1 == *.tar.gz ]]; then
    echo ".tar.gz"
    return
  fi
  if [[ $1 == *.tar.bz2 ]]; then
    echo ".tar.bz2"
    return
  fi
  if [[ $1 == *.tar ]]; then
    echo ".tar"
    return
  fi
  if [[ $1 == *.zip ]]; then
    echo ".zip"
    return
  fi
  if [[ $1 == *.rar ]]; then
    echo ".rar"
    return
  fi
  if [[ $1 == *.xz ]]; then
    echo ".xz"
    return
  fi
  if [[ $1 == *.7z ]]; then
    echo ".7z"
    return
  fi
}

function oeg_get_basename_with_version {
  local EXTENSION=$(oeg_get_extension $1)   # or =`exp`

  echo "`basename $1 $EXTENSION`"
}

function oeg_get_basename {
  local REGEXP='(.*)-([[:digit:]].*)'
  if [[ $(oeg_get_basename_with_version $1) =~ $REGEXP ]]
  then
     echo "${BASH_REMATCH[1]}"
  else
     echo ""       # Could not split basename and version.
  fi
}

function oeg_get_version {
  local REGEXP='(.*)-([[:digit:]].*)'
  if [[ $(oeg_get_basename_with_version $1) =~ $REGEXP ]]
  then
     echo "${BASH_REMATCH[2]}"
  else
     echo "0"      # Could not split basename and version.
  fi
}

# If file name doesn't contain a hyphen then the whole file name has to be given.
# If there is exactly one hyphen then it is splitted as name-version. If there are
# more than one hyphens, the first hyphen immediately followed by a numerical digit
# is the one we are looking for.

function oegextract {
  if [ ! $# == 1 ]; then
    echo "Usage: oegextract (\"name\" [\"version\"] | <full file name>)"
    return
  fi

  if [ "$1" = "" ]; then
    echo "Error: File name was empty."
    return
  fi

  if [ "$1" = "*" ]; then
    echo "Error: File name matches all files."
    return
  fi

  if [ "$2" = "" ]; then
    if [ "$OEG_DEBUG" = "1" ]; then
      echo "No version given.";
    fi
  fi

  cd ${OEG_WORK_DIR}

  SEL_BASENAME=
  SEL_VERSION=
  SEL_EXTENSION=

  if [ -f "$OEG_DOWNLOADS_DIR/$1" ]              # Got a complete file name with path.
  then
    oegextractwithfilename "$1"
    return
  fi

  for file in $OEG_DOWNLOADS_DIR/$1-*; do
    # Or use "shopt -s nullglob" to avoid the look for the "*"?
    if [[ "$file" =~ "\*" ]]; then
      if [ "$OEG_DEBUG" = "1" ]; then
        echo "'$file' contains '*'. Ignored!";
      fi
    else
      echo "Found: $file"

      local FILE_BASENAME=`oeg_get_basename $file`
      local FILE_VERSION=`oeg_get_version $file`
      local FILE_EXTENSION=`oeg_get_extension $file`

      if [ "$OEG_DEBUG" = "1" ]; then
        echo "NAME = $FILE_BASENAME"
        echo "VERSION = $FILE_VERSION"
        echo "EXTENSION = $FILE_EXTENSION"
      fi

      if [ "$SEL_BASENAME" = "" ]; then
        SEL_BASENAME=$FILE_BASENAME
        SEL_VERSION=$FILE_VERSION
        SEL_EXTENSION=$FILE_EXTENSION
      fi

      if [ "$SEL_BASENAME" != "$FILE_BASENAME" ]; then               # Next file with a different basename?
        echo "Error: More than one basename found. Selecting exact matches only.";
        if [ "$OEG_DEBUG" = "1" ]; then
          echo "Selected: $SEL_BASENAME; found: $FILE_BASENAME";
        fi

        if [ "$SEL_BASENAME" \> "$FILE_BASENAME" ]; then
          SEL_BASENAME=$FILE_BASENAME
          SEL_VERSION=$FILE_VERSION
          SEL_EXTENSION=$FILE_EXTENSION
        fi
      fi

      if [ ! "$SEL_VERSION" = "$FILE_VERSION" ]; then                # Different version numbers.
        compareversions $SEL_VERSION $FILE_VERSION
        if [ "$?" = "2" ]; then                                      # SEL_VERSION < FILE_VERSION.
          if [ "$OEG_DEBUG" = "1" ]; then
            echo "Newer file ($FILE_VERSION) selected."
          fi

          SEL_BASENAME=$FILE_BASENAME
          SEL_VERSION=$FILE_VERSION
          SEL_EXTENSION=$FILE_EXTENSION
        fi
      fi

# TODO: regexp for file names with multiple hyphens, other chars or without version numbers.

#  local REGEXP='(.*)-([[:digit:]].*)'
#  if [[ $(oeg_get_basename_with_version $file) =~ $REGEXP ]]
#  then
#     echo "1 ${BASH_REMATCH[1]}"
#     echo "2 ${BASH_REMATCH[2]}"
#     echo "3 ${BASH_REMATCH[3]}"
#  else
#     echo "Could not split basename and version."
#  fi

    fi
  done

  if [ "$SEL_BASENAME" = "" ]; then
    echo "Error: No file found."
    return
  fi

  if [ "$OEG_DEBUG" = "1" ]; then
    echo "Selected: $SEL_BASENAME-$SEL_VERSION$SEL_EXTENSION"
  fi

  oegextractwithfilename "$SEL_BASENAME-$SEL_VERSION$SEL_EXTENSION"
}

function oegextractwithfilename {
  if [ ! $# == 1 ]; then
    echo "Usage: oegextract \"name-version.extension\""
    return
  fi

  if [ "$1" = "" ]; then
    echo "Error: File name was empty."
    return
  fi

  if [ ! -f "$OEG_DOWNLOADS_DIR/$1" ]
  then
    echo Error: The file does not exist.
    return
  fi

  cd ${OEG_WORK_DIR}

  export FILENAME=$OEG_DOWNLOADS_DIR/$1
  echo "Extracting: ${FILENAME}"

  if [[ $FILENAME == *.tar.gz ]]; then
    export FILEEXTENSION=.tar.gz
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}" -so | "${OEG_PATH_TO_7ZIP}" x -si -ttar -y
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.tar.bz2 ]]; then
    export FILEEXTENSION=.tar.bz2
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}" -so | "${OEG_PATH_TO_7ZIP}" x -si -ttar -y
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.tar ]]
  then
    export FILEEXTENSION=.tar
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}"
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.zip ]]
  then
    export FILEEXTENSION=.zip
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}"
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.7z ]]
  then
    export FILEEXTENSION=.7z
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}"
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.tar.xz ]]
  then
    export FILEEXTENSION=.tar.xz
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    "${OEG_PATH_TO_7ZIP}" x "${FILENAME}" -so | "${OEG_PATH_TO_7ZIP}" x -si -ttar -y
    cd "$OEG_WORK_DIR/$OUTPUTDIR"
    return
  fi

  if [[ $FILENAME == *.tar.lz ]]
  then
    export FILEEXTENSION=.tar.lz
    export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
    echo Output Directory: ${OUTPUTDIR}

    if [ -d "$OEG_WORK_DIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

    #"${OEG_PATH_TO_7ZIP}" x "${FILENAME}" -so | "${OEG_PATH_TO_7ZIP}" x -si -ttar -y
    #cd "$OEG_WORK_DIR/$OUTPUTDIR"
    echo Error: .tar.lz archive...
    return
  fi

  if [[ $FILENAME == *.xz ]]
  then
    echo XZ archive unhandled
    return
  fi

  echo Unknown file or archive format. Don\'t know how to extract...
}

# Extracts a binary archive into the base directory ("/open-egovernment").

function oegimportwithfilename {
  if [ ! $# == 1 ]; then
    echo "Usage: oegimportwithfilename \"name-version\""
    return
  fi

  if [ "$1" = "" ]; then
    echo "Error: name was empty."
    return
  fi

  if [ "$TARGETBITS" = "" ]; then
    echo "Error: unknown target platform (32 or 64 bits?), call oegenv()"
    return
  fi

  pushd .

  cd "${OEG_BASE_DIR}"
  case "${OEG_ARCHIVE_FORMAT}" in
    '7z')
      echo "Searching for 7-zip binary archive ..."
      echo "Filename: ${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      "${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      ;;
    'zip')
      echo "Searching for zip binary archive ..."
      "${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      ;;
    *)
      echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
      ;;
  esac

  popd

  # After importing the archive, make an entry to the file dependencies.txt
  # in the installation directory. Later, this will be included into the
  # binaries archive of the current package.

  mkdir -p ${OEG_INSTALL_DIR}${OEG_BASE_DIR}               # The directory needs to be already there!

  # TODO: Do not log imports depending on the already logged package!
  # Put the data into the dependencies file only if it isn't the current package itself.

  echo "$1" >> "${OEG_INSTALL_DIR}${OEG_BASE_DIR}/dependencies.txt"
}

function oegimport {
  if [ ! $# == 1 ]; then
    echo "Usage: oegimport \"name\" [\"version\"]"                   # TODO: flags, dependencies.
    return
  fi

  if [ "$1" = "" ]; then
    echo "Error: name was empty."
    return
  fi

  if [ "$TARGETBITS" = "" ]; then
    echo "Error: unknown target platform (32 or 64 bits?), call oegenv()"
    return
  fi

  if [ -f "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}" ]           # Got a complete file name with path.
  then
    oegimportwithfilename "$1"
    return
  fi

  SEL_BASENAME=
  SEL_VERSION=

  shopt -s nullglob
  for file in ${OEG_ARCHIVES_DIR}/$1-*.${OEG_ARCHIVE_FORMAT}; do
    if [ "$OEG_DEBUG" = "1" ]; then
      echo "Found: $file"
    fi

    local FILE_BASENAME=`oeg_get_basename $file`
    local FILE_VERSION=`oeg_get_version $file`

    if [ "$OEG_DEBUG" = "1" ]; then
      echo "NAME = $FILE_BASENAME"
      echo "VERSION = $FILE_VERSION"
    fi

    if [ "$SEL_BASENAME" = "" ]; then
      SEL_BASENAME=$FILE_BASENAME
      SEL_VERSION=$FILE_VERSION
    fi

    if [ "$SEL_BASENAME" != "$FILE_BASENAME" ]; then                 # Next file with a different basename?
      echo "Error: More than one basename found. Selecting exact matches only.";
      if [ "$OEG_DEBUG" = "1" ]; then
        echo "Selected: $SEL_BASENAME; found: $FILE_BASENAME";
      fi

      if [ "$SEL_BASENAME" \> "$FILE_BASENAME" ]; then
        SEL_BASENAME=$FILE_BASENAME
        SEL_VERSION=$FILE_VERSION
      fi
    fi

    if [ ! "$SEL_VERSION" = "$FILE_VERSION" ]; then                  # Different version numbers.
      compareversions $SEL_VERSION $FILE_VERSION
      if [ "$?" = "2" ]; then                                        # SEL_VERSION < FILE_VERSION.
        if [ "$OEG_DEBUG" = "1" ]; then
          echo "Newer file ($FILE_VERSION) selected."
        fi

        SEL_BASENAME=$FILE_BASENAME
        SEL_VERSION=$FILE_VERSION
      fi
    fi
  done
  shopt -u nullglob

  if [ "$SEL_BASENAME" = "" ]; then
    echo "Error: No file found."
    return
  fi

  if [ "$2" = "" ] || [ "$OEG_DEBUG" = "1" ]; then                   # Version parameter was empty.
    echo "Selected: $SEL_BASENAME-$SEL_VERSION"
  fi

  # Look for the dependencies file and import them too!

  oegimportwithfilename "$SEL_BASENAME-$SEL_VERSION"
}

