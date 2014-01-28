# $Id$
#
# This file contains functions to help while building required packages
# without pre-built archives or the builder application. It is needed
# e.g. if the compiler changed or was updated and the builder is unable
# to build new OSS library binaries because the existing binary archives
# are incompatible with the current tools.
#
# Run a MSYS shell and source this file!

# TODO:
#
# * use own temporary work directories for multiple sessions
# * recursive oegimport function
# * oegimportwithfilename: show errors if needed. missing space, file already exists, ...

# Patches certain fields of a named libtool archive file.
# Example call:
# oeg_fix_libtool_file libiconv.la libiconv-2.dll libiconv.dll.a libiconv.a
# Changes these values:
#dlname='../bin/libiconv-2.dll'
#dlname='../bin64/libiconv-2.dll'
#library_names='libiconv.dll.a'
#old_library='libiconv.a'
#libdir='/open-egovernment/lib'
#libdir='/open-egovernment/lib64'

# empty parameters "" are allowed

function oeg_fix_libtool_file {
  local TARGETBITSFORDIR=""

  if [ "${TARGETBITS}" == "64" ]; then
    TARGETBITSFORDIR="64"
  fi

  if [ ! -f "lib${TARGETBITSFORDIR}/$1" ]; then
    echo "libtool archive file not found: lib${TARGETBITSFORDIR}/$1"
    return
  fi

  libtool --finish "lib${TARGETBITSFORDIR}/$1"

  # If we use -i (inline edit) then we get an error:
  # sed: preserving permissions for `lib/sed003912': Permission denied
  # It's caused by the windows security. In the folder's properties dialog,
  # select the security option, then grant all privelega to the current user.
  # If you try without this setting, the la file will become read-only.

  if [ "$2" == "" ]; then
    sed -e "s/dlname='.*'/dlname='$2'/g" "lib${TARGETBITSFORDIR}/$1" > "lib${TARGETBITSFORDIR}/$1.new"
  else
    sed -e "s/dlname='.*'/dlname='..\/bin${TARGETBITSFORDIR}\/$2'/g" "lib${TARGETBITSFORDIR}/$1" > "lib${TARGETBITSFORDIR}/$1.new"
  fi
  mv -f "lib${TARGETBITSFORDIR}/$1.new" "lib${TARGETBITSFORDIR}/$1"

  sed -e "s/library_names='.*'/library_names='$3'/g" "lib${TARGETBITSFORDIR}/$1" > "lib${TARGETBITSFORDIR}/$1.new"
  mv -f "lib${TARGETBITSFORDIR}/$1.new" "lib${TARGETBITSFORDIR}/$1"
  sed -e "s/old_library='.*'/old_library='$4'/g" "lib${TARGETBITSFORDIR}/$1" > "lib${TARGETBITSFORDIR}/$1.new"
  mv -f "lib${TARGETBITSFORDIR}/$1.new" "lib${TARGETBITSFORDIR}/$1"
  sed -e "s/libdir='.*'/libdir='\\${OEG_BASE_DIR}\/lib${TARGETBITSFORDIR}'/g" "lib${TARGETBITSFORDIR}/$1" > "lib${TARGETBITSFORDIR}/$1.new"
  mv -f "lib${TARGETBITSFORDIR}/$1.new" "lib${TARGETBITSFORDIR}/$1"

  # TODO: dependency_libs=' -L/lib64 ' is wrong
}

# Correct wrong path names and moves the contents to the correct path.
# * bin -> bin64, lib -> lib64 if 64 bit environment

function oeg_fix_path_names {
  cd "${OEG_INSTALL_DIR}${OEG_BASE_DIR}"

  if [ "${TARGETBITS}" == "64" ]; then
    if [ -d bin ]; then
      mkdir -p bin64
      mv -i bin/* bin64/                         # Contains normally only *.exe and *.dll files.
      rm -rf bin
    fi
    if [ -d lib ]; then
      mkdir -p lib64
      mv -i lib/* lib64/                         # Contains normally only *.a and *.la files.
      rm -rf lib
    fi
  fi
}

#

function oeg_include_configure_flags {
  :
}

# Add a file to the packages/name-version/ directory of the archive.

function oeg_include_file {
  if [ ! -f "$1" ]; then
    echo File $1 does not exist!
    return
  fi

  local OEG_ADD_FILES_DIR="${OEG_INSTALL_DIR}${OEG_BASE_DIR}/packages/${PACKAGE_NAME}-${PACKAGE_VERSION}"
  mkdir -p "${OEG_ADD_FILES_DIR}"
  cp "$1" "${OEG_ADD_FILES_DIR}/"
}

# Add a file or a list of files to the packages/name-version/
# directory of the archive. Currently unused.

function oeg_include_files {
  if [ $# == 0 ]; then
    echo "Usage: oeg_include_files <file1> [<file2>] ..."
    return
  fi

  for file in "$@"
  do
    oeg_include_file "$file"
  done
}

# Includes the configure help text into the package
# which allows to check for other possible flags or
# packages without opening the builder or installing
# the package sources first.

function oeg_include_configure_output {
  local OEG_CONFIGURE_HELP_FILE="/tmp/configure-help.txt"
  configure --help > ${OEG_CONFIGURE_HELP_FILE}

  oeg_include_file ${OEG_CONFIGURE_HELP_FILE}
  rm -f ${OEG_CONFIGURE_HELP_FILE}
}

# Copies the dependencies.txt file, where every oegimport
# was logged, to the packages/name-version/ directory.

function oeg_include_dependencies {
  oeg_include_file "${OEG_DEPENDENCIES_FILE}"
}

# After importing an archive, make an entry to the file dependencies.txt
# in the work directory. Later, this will be included into the binary
# archive of the current package. So all imports may be reimported again
# automatically when installing the newly created binary archive.

function oeg_add_to_current_dependencies_file {
  mkdir -p ${OEG_WORK_DIR}                                           # The directory needs to be already there!
  echo "$1" >> "${OEG_DEPENDENCIES_FILE}"
}

# Add infos: time needed, system, compiler, flags, current date.

function oeg_include_build_info_file {
  echo "Package: ${PACKAGE_NAME}"
  echo "Version: ${PACKAGE_VERSION}"
  echo "Date: `date +\"%T %d.%m.%Y %Z\"`"
  echo "Time needed: "
  echo "Compiler: `gcc -v`"
  echo "Host: `gcc -dumpmachine`"
}

# Inserts a file about the OEG project.

function oeg_include_oeg_info_file {
  cp "${OEG_PROJECT_DIR}/info.txt" /tmp/Open\ E-Government.txt
  oeg_include_file /tmp/Open\ E-Government.txt
}

# Creates a list of all setup files and adds it to the archive.
# The list doesn't contain information about files below the
# packages directory (no OEG files and no manually included files).
# It is needed to check for possible conflicts with already imported
# packages before importing a package.

function oeg_include_file_list {
  find . | grep -v "./packages" | grep -v "^.$" > /tmp/file-list.txt
  oeg_include_file /tmp/file-list.txt
  rm -f /tmp/file-list.txt
}

# Called from oegimport. Looks into all extracted dependencies.txt files
# and imports all dependencies which are not already imported. If a package
# is already imported will be determined by looking for the corresponding
# packages/name-version directory. This function ensures, that all imports
# are recursively applied and no archive will imported twice.

function oeg_import_dependencies {
  echo "Importing dependencies:"

  local OEG_REQUIRED_DEPS_FILE="/work/required-deps.txt"

  if [ -f "${OEG_REQUIRED_DEPS_FILE}" ]; then              # We call ourself recursively. Don't create a new file.
    return                                                 # We delete it at the end of all imports and then we
  fi                                                       # call this function again to install the open requirements.

  cat ${OEG_BASE_DIR}/packages/*/dependencies.txt | sort | uniq > "${OEG_REQUIRED_DEPS_FILE}"

  if [ -f "${OEG_REQUIRED_DEPS_FILE}.old" ]; then          # We compare the old file against the new one and if
    if $(diff "${OEG_REQUIRED_DEPS_FILE}" "${OEG_REQUIRED_DEPS_FILE}.old"); then  # both are identical that
      rm -f "${OEG_REQUIRED_DEPS_FILE}" "${OEG_REQUIRED_DEPS_FILE}.old"           # means there are no new
      return                                               # dependencies to install. We break our loop.
    fi
  fi                                                                 

  while read REQUIRED_DEPENDENCY ; do                      # Read required deps file line by line.
    echo "${REQUIRED_DEPENDENCY}"
    if [ ! -d "${OEG_BASE_DIR}/packages/${REQUIRED_DEPENDENCY}" ]    # There isn't already an installed package with this name.
    then
      oegimportwithfilename "${REQUIRED_DEPENDENCY}"
      #counter=`expr $counter + 1`;
    fi
  done < "${OEG_REQUIRED_DEPS_FILE}"                        # From a file, redirection with <(cmd) fails here.

  mv -f "${OEG_REQUIRED_DEPS_FILE}" "${OEG_REQUIRED_DEPS_FILE}.old"  # We remove this file to allow us to rescan everything.

  # TODO: Ignore not existing requirements with an error message.

  oeg_import_dependencies                                  # Repeat until all open requirements are installed.
}

function oegdebug {
  if [ ! $# == 1 ]; then
    echo "Usage: oegdebug <1 or 0>"
    return
  fi

  export OEG_DEBUG="$1"
}

# Sets the path to the MinGW binary directory.

function oeg_mingw_path {
  if [ ! $# == 1 ]; then
    echo "Usage: oeg_mingw_path <32 or 64 bits as number>"
    return
  fi

  if [ "$1" = "32" ]; then
    export PATH=/d/dev/mingw32/bin:$PATH
  elif [ "$1" = "64" ]; then
    export PATH=/d/dev/mingw64/bin:$PATH
  else
    echo Wrong parameter: $1
    return
  fi
}

# Sets the Qt path. Separated from setting the MinGW path to allow
# building open source software with a clean environment, which means
# there is no possibility that configure uses libraries or tools from
# the Qt directories by accident.

function oeg_qt_path {
  if [ ! $# == 1 ]; then
    echo "Usage: oeg_qt_path <32 or 64 bits as number>"
    return
  fi

  if [ "$1" = "32" ]; then
    export PATH=/d/dev/Qt-5.2.0-i686/bin:$PATH
  elif [ "$1" = "64" ]; then
    export PATH=/d/dev/Qt-5.2.0-x86_64/bin:$PATH
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

  export EDITOR="/c/Program Files (x86)/Notepad++/notepad++.exe"
  export OEG_BASE_DIR="/open-egovernment"
  export OEG_INSTALL_DIR="/open-egovernment-install"
  export OEG_WORK_DIR="/work"
  export OEG_PROJECT_DIR="/i/Projekte/open-egov"
  export OEG_DOWNLOADS_DIR="${OEG_PROJECT_DIR}/data/builder/downloads"
  export OEG_PATCHES_DIR="${OEG_PROJECT_DIR}/data/builder/patches"
  export OEG_DEPENDENCIES_FILE="${OEG_WORK_DIR}/dependencies.txt"

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

  # Show the list of files while extracting an archived package? This could hide
  # error messages (filesystem full, e.g. if you have MSYS/MinGW in a RAM disk).
  export OEG_CFG_SHOW_FILES_WHILE_IMPORT="no"

  # While oegimport: Show the full archive file name or is a "ok" (=found it) enough?
  export OEG_CFG_IMPORT_SHOW_FULL_FILE_NAME="no"

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

  oeg_mingw_path $1
  #oeg_qt_path $1
  export PATH="${OEG_BASE_BIN_DIR}:${PATH}"                          # At first place!

  export CVS_RSH=ssh

  export CXXFLAGS="$CFLAGS"
  export CPPFLAGS="-I${OEG_BASE_DIR}/include"

  export OEG_ARCHIVES_DIR="${OEG_PROJECT_DIR}/data/builder/archives/windows-${TARGETBITS}"

  mkdir -p ${OEG_WORK_DIR} ${OEG_BASE_DIR} ${OEG_INSTALL_DIR}        # In case they are missing...
  cd ${OEG_WORK_DIR}
}

function oegpatch {
  if [ ! $# == 1 ]; then
    echo "Usage: oegarchive <number of patch file>"
    return
  fi

  #create: diff -Naur src.old src.new > patch.txt
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
      echo "Error: The target file already existed and was deleted!"
      rm -f "${ARCHIVEFILENAME}.${OEG_ARCHIVE_FORMAT}"
    fi
  fi

  # Insert text files about the OEG project, the required dependencies, ... here.

  oeg_include_dependencies
  oeg_include_build_info_file
  oeg_include_oeg_info_file
  oeg_include_file_list

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

function oeg_clean_install_dir {
  cd /
  rm -rf ${OEG_INSTALL_DIR}
  mkdir ${OEG_INSTALL_DIR}
}

function oeg_clean_base_dir {
  cd /
  rm -rf ${OEG_BASE_DIR}
  mkdir ${OEG_BASE_DIR}
}

function oeg_clean_work_dir {
  cd /
  rm -rf ${OEG_WORK_DIR}
  mkdir ${OEG_WORK_DIR}

  cd ${OEG_WORK_DIR}
}

function oegclean {
  oeg_clean_base_dir
  oeg_clean_install_dir
  oeg_clean_work_dir                   # last position, changes into work dir
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

  mkdir -p ${OEG_WORK_DIR}
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

      if [ "$SEL_BASENAME" != "$FILE_BASENAME" ]; then     # Next file with a different basename?
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

# Extracts a source archive into the work directory and changes into it.

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

  mkdir -p "${OEG_WORK_DIR}"
  rm -f "${OEG_DEPENDENCIES_FILE}"               # Remove old entries from other packages.
  touch "${OEG_DEPENDENCIES_FILE}"               # Ensures, every package gets such a file included.

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
# The function gets the basename and version of the package as parameter.

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

  local OEG_IMPORT_FILENAME="${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"

  if [ -f "${OEG_IMPORT_FILENAME}" ]
  then
    if [ "$OEG_CFG_IMPORT_SHOW_FULL_FILE_NAME" = "yes" ]; then
      echo "Found file: ${OEG_IMPORT_FILENAME}"
    fi
  else
    echo "Error: The file ${OEG_IMPORT_FILENAME} does not exist."
    return
  fi

  # Ignore this function call if the archive was already imported. Don't import twice!

  if [ -f "${OEG_DEPENDENCIES_FILE}" ]; then
    if $(grep -q "$1" "${OEG_DEPENDENCIES_FILE}"); then
      echo "Package already imported (skipped): $1"
      return
    fi
  fi

  pushd . > /dev/null
  cd "${OEG_BASE_DIR}"

  if [ "$OEG_CFG_SHOW_FILES_WHILE_IMPORT" = "no" ]; then
    case "${OEG_ARCHIVE_FORMAT}" in
      '7z')
        if $("${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}" | grep -q 'Everything is Ok') ; then
          # 30-37: set foreground color, 40-47: set background color, 0: normal screen.
          #echo -e "\033[42m\033[37mArchive extracted.\033[0m"
          :
        else
          echo -e "\033[41m\033[37mError while extracting archive!\033[0m"
        fi
        ;;
      'zip')
        "${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}" > /dev/null
        ;;
      *)
        echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
        ;;
    esac
  else
    case "${OEG_ARCHIVE_FORMAT}" in
      '7z')
        echo
        "${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}" | grep -v -e "Processing archive" -e "Copyright (c) 1999-2011 Igor Pavlov" -e "Folders: " -e "Files: " -e "Size: " -e "Compressed: " -e "Everything is Ok" -e "^$"
        echo
        ;;
      'zip')
        "${OEG_PATH_TO_7ZIP}" x -y "${OEG_ARCHIVES_DIR}/$1.${OEG_ARCHIVE_FORMAT}"
        ;;
      *)
        echo "Unknown binary archive format: \"${OEG_ARCHIVE_FORMAT}\"!"
        ;;
    esac
  fi

  popd > /dev/null

  local DEPS_FILE="${OEG_BASE_DIR}/packages/$1/dependencies.txt"
  if [ ! -f "${DEPS_FILE}" ]; then
    echo "Dependencies file not found."
  fi

  # Do not log imports depending on the already logged package!

  if [ "${PACKAGE_NAME}-${PACKAGE_VERSION}" != "$1" ]; then          # Log the data only if it isn't the current package itself.
    oeg_add_to_current_dependencies_file "$1"                        # Log the import into dependencies.txt file.
  fi

  # We just imported an package into ${OEG_BASE_DIR}. Its dependencies can be found
  # in ${OEG_BASE_DIR}/packages/name-version/dependencies.txt. Read it and add all
  # missing depending packages to the import list.

  oeg_import_dependencies                                            # Recursively import all dependent packages.
}

# This function imports a package without a version parameter.
# It looks for all files starting with the "name" parameter and
# tries to select the newest.

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
    # Show the selected archive to be able to verify the correct version.
    echo "Importing: $SEL_BASENAME-$SEL_VERSION"
  fi

  # Look for the dependencies file and import them too!

  oegimportwithfilename "$SEL_BASENAME-$SEL_VERSION"
}

