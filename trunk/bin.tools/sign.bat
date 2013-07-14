@echo off

rem $Id$

cd /d %0\..\..\bin.tools

if not exist "%1" goto filenotfound

echo Signing executable ...

if not exist "signtool.exe" goto sign_skip_1
"signtool.exe" sign "%1"
goto sign_end

:sign_skip_1
if not exist "C:\Programme\Microsoft Visual Studio 8\Common7\Tools\Bin\signtool.exe" goto sign_skip_2
"C:\Programme\Microsoft Visual Studio 8\Common7\Tools\Bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_2
if not exist "D:\Programme\Microsoft Visual Studio 8\Common7\Tools\Bin\signtool.exe" goto sign_skip_3
"D:\Programme\Microsoft Visual Studio 8\Common7\Tools\Bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_3
if not exist "C:\Program Files\Microsoft SDKs\Windows\v7.0A\bin\signtool.exe" goto sign_skip_4
"C:\Program Files\Microsoft SDKs\Windows\v7.0A\bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_4
if not exist "C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin\signtool.exe" goto sign_skip_5
"C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_5
if not exist "C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\Bin\signtool.exe" goto sign_skip_6
"C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\Bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_6
if not exist "C:\WinDDK\7600.16385.1\bin\amd64\signtool.exe" goto sign_skip_7
"C:\WinDDK\7600.16385.1\bin\amd64\signtool.exe" sign "%1"
goto sign_end

:sign_skip_7
if not exist "C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\signtool.exe" goto sign_skip_8
"C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\signtool.exe" sign "%1"
goto sign_end

:sign_skip_8
if not exist "C:\WinDDK\7600.16385.1\bin\x86\signtool.exe" goto sign_end
"C:\WinDDK\7600.16385.1\bin\x86\signtool.exe" sign "%1"

:sign_end
echo Signing finished.
goto end

rem Error messages.

:filenotfound
echo Error: File "%1" not found.
goto end

:end

