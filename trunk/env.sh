# $Id$
#
# This file contains functions to help while building required packages
# without prebuilt archives or the builder application. It is needed e.g.
# if the compiler changed or was updated and the builder is unable to
# build new OSS library binaries because the existing binary archives
# are incompatible with the current tools.
#
# Run a MSYS shell and source this file!

function oegenv {
  if [ ! $# == 1 ]; then
    echo "Usage: oegenv <32 or 64 bits as number>"  # not $0
    return   # don’t use exit!
  fi

  export BASEDIR="/open-egovernment"
  export OEG_BASE_DIR_INSTALL="/open-egovernment-install"
  export WORKDIR="/work"
  export OEGDIR="/i/Projekte/open-egov"
  export OEG_DOWNLOADS_DIR="${OEGDIR}/data/builder/downloads"
  export OEG_PATCHES_DIR="${OEGDIR}/data/builder/patches"

  export CXXFLAGS="$CFLAGS"
  export CPPFLAGS=""
  export LINGUAS="en de ar ru"
  export LANG=de

  #export PATH_TO_7ZIP="/c/Programme/7-Zip/7z.exe"
  export PATH_TO_7ZIP="/c/Program Files/7-Zip/7z.exe"

  #export OEG_ARCHIVE_FORMAT="zip"
  export OEG_ARCHIVE_FORMAT="7z"

  # When installing to $OEG_BASE_DIR_INSTALL: Do we want a "make install" or "make install-strip"?
  export OEG_CFG_MAKE_INSTALL_STRIP="yes"

  # Should oegarchive remove or update the target archive if there already exists one?
  export OEG_CFG_REMOVE_BINARY_ARCHIVE="yes"

  local STDCFLAGS="-pipe -O2 -mms-bitfields -fomit-frame-pointer -I$BASEDIR/include"

  if [ "$1" = "32" ]; then
    export CFLAGS="-m32 -march=i686 -mtune=i686 $STDCFLAGS"
    export LDFLAGS="-m32 -pipe -L$BASEDIR/lib"
    export TARGETBITS="32"
    export CONFIGURE_HOST_PARA="--host=i686-w64-mingw32"
  elif [ "$1" = "64" ]; then
    export CFLAGS="-m64 -march=nocona -mtune=core2 $STDCFLAGS"
    export LDFLAGS="-m64 -pipe -L$BASEDIR/lib64"
    export TARGETBITS="64"
    export CONFIGURE_HOST_PARA="--host=x86_64-w64-mingw32"
  else
    echo Wrong parameter: $1
    return
  fi

  export OEG_ARCHIVES_DIR="${OEGDIR}/data/builder/archives/windows-${TARGETBITS}"
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

  cd "${OEG_BASE_DIR_INSTALL}/open-egovernment"

  if [ -f "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" ]; then
    if [ "$OEG_CFG_REMOVE_BINARY_ARCHIVE" = "yes" ]; then
      echo Error: The target file already existed and got deleted!
      rm -rf "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}"
    fi
  fi

  case "${OEG_ARCHIVE_FORMAT}" in
    '7z')
      echo "Creating a 7-zip binary archive ..."
      "$PATH_TO_7ZIP" a -mx9 -t7z -ms -mmt -w.. "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" .
      ;;
    'zip')
      echo "Creating a zip binary archive ..."
      "$PATH_TO_7ZIP" a -tzip -w.. "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}" .
      ;;
    *)
      echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
      echo "Error: No archive created!"
      return
      ;;
  esac
}

function oegcleanbase {
  cd $WORKDIR

  rm -rf ${BASEDIR}
  mkdir ${BASEDIR}

  rm -rf ${OEG_BASE_DIR_INSTALL}
  mkdir ${OEG_BASE_DIR_INSTALL}
}

function oegextract {
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

  cd ${WORKDIR}
  export FILENAME=$OEG_DOWNLOADS_DIR/$1
  echo "Extracting: ${FILENAME}"

  if [[ $FILENAME == *.tar.gz ]]; then
    export FILEEXTENSION=.tar.gz
	export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
	echo Output Directory: ${OUTPUTDIR}

    if [ -d "$WORKDIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

	"${PATH_TO_7ZIP}" x "${FILENAME}" -so | "${PATH_TO_7ZIP}" x -si -ttar -y
	cd "$WORKDIR/$OUTPUTDIR"
	return
  fi

  if [[ $FILENAME == *.tar.bz2 ]]; then
    export FILEEXTENSION=.tar.bz2
	export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
	echo Output Directory: ${OUTPUTDIR}

    if [ -d "$WORKDIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

	"${PATH_TO_7ZIP}" x "${FILENAME}" -so | "${PATH_TO_7ZIP}" x -si -ttar -y
	cd "$WORKDIR/$OUTPUTDIR"
	return
  fi

  if [[ $FILENAME == *.tar ]]
  then
    echo TAR archive unhandled
	return
  fi

  if [[ $FILENAME == *.zip ]]
  then
    export FILEEXTENSION=.zip
	export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
	echo Output Directory: ${OUTPUTDIR}

    if [ -d "$WORKDIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

	"${PATH_TO_7ZIP}" x "${FILENAME}"
	cd "$WORKDIR/$OUTPUTDIR"
	return
  fi

  if [[ $FILENAME == *.7z ]]
  then
    echo 7z archive unhandled
	return
  fi

  if [[ $FILENAME == *.tar.xz ]]
  then
    export FILEEXTENSION=.tar.xz
	export OUTPUTDIR=`basename $FILENAME $FILEEXTENSION`
    echo Extension: ${FILEEXTENSION}
	echo Output Directory: ${OUTPUTDIR}

    if [ -d "$WORKDIR/$OUTPUTDIR" ]
    then
      echo Error: The output directory already exists. Remove it first.
      return
    fi

	"${PATH_TO_7ZIP}" x "${FILENAME}" -so | "${PATH_TO_7ZIP}" x -si -ttar -y
	cd "$WORKDIR/$OUTPUTDIR"
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

function oegimport {
  if [ ! $# == 1 ]; then
    echo "Usage: oegimport \"name-version\""
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

  pushd .

  cd "${BASEDIR}"
  case "${OEG_ARCHIVE_FORMAT}" in
    '7z')
      echo "Searching for 7-zip binary archive ..."
      echo "Filename: ${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      "${PATH_TO_7ZIP}" x "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      ;;
    'zip')
      echo "Searching for zip binary archive ..."
      "${PATH_TO_7ZIP}" x "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
      ;;
    *)
      echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
      ;;
  esac

  popd
}

