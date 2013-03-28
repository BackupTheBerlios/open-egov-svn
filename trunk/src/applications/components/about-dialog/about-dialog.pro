# $Id$

TEMPLATE = subdirs
SUBDIRS  = src

exists(application.xml) {
  message("application.xml found!")

  system(..\..\..\..\bin\createsources.exe --verbose application.xml)
}
else {
  message("No application.xml found!")
}

