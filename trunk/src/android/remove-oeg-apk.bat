@ECHO OFF

REM $Id$

TITLE APK Remover
ECHO Removing all OEG APKs from Device.

SET PATH=%PATH%;C:\Program Files (x86)\Android\android-sdk\platform-tools
SET PATH=%PATH%;C:\Program Files (x86)\Android\android-sdk\tools

adb uninstall xxx.apk

PAUSE

