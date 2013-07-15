# $Id$
#
# Parses the application.xml and creates needed source files.

# See Qt bugs #4329, #8430.
# With $$OUT_PWD we have a fixed point to start with.
# $$PWD contains only the pro/pri directory.

# $$OUT_PWD contains something like: C:/Test/123. Windows dislikes it.
contains(DIR_SEPARATOR, "\\") {
  PRO_OUT_PATH = $$replace(OUT_PWD, "/", "\\")
  #message($${PRO_OUT_PATH})
}
else {
  PRO_OUT_PATH = $$OUT_PWD
}

message("PRO_OUT_PATH is $${PRO_OUT_PATH}")

exists($${PRO_OUT_PATH}$${DIR_SEPARATOR}application.xml) {
  message("application.xml found!")

  system(..$${DIR_SEPARATOR}..$${DIR_SEPARATOR}bin$${DIR_SEPARATOR}createsources.exe --verbose $${PRO_OUT_PATH}$${DIR_SEPARATOR}application.xml)
}
else {
  message("No application.xml found!")
}

