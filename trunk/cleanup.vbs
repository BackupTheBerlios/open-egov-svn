' $Id$

' Script for MinGW/Windows environments to remove all temporary files
' without removing notes and additional files. Needed because it was
' not possible to automatically remove all object files and other
' generated files (which is required after bigger changes of certain
' OEG classes). This gets a "fresh" copy without the need to reimport
' virgin sources from SVN.
' You may call the script from the command line: cscript path\cleanup.vbs

Option Explicit

Const DebugOutputDeletedNames  = true
Const DebugOutputMissedNames   = true

' Initializations.

Dim shell: Set shell = WScript.CreateObject("WScript.Shell")
Dim fso: Set fso = CreateObject("Scripting.FileSystemObject")

Dim foldername, s
Dim folders, folder, files, file
Dim folder2

foldername = Wscript.ScriptFullName & "\.."

If Not fso.FolderExists(foldername) Then
  MsgBox "Could not find base directory to operate from.", vbOKOnly + vbInformation, "Error"
  WScript.Quit
End If

Set folder  = fso.GetFolder(shell.ExpandEnvironmentStrings(foldername))
Set files   = folder.Files
Set folders = folder.SubFolders

' The "\.." are removed from the foldername now.
foldername = fso.GetAbsolutePathName(folder)

' Enable to debug; Should contain the full directory name to the folder containing this script.
'Wscript.Echo foldername

s = foldername & "\src\applications"
For Each folder In fso.getFolder(s).SubFolders
  If folder.Name <> ".svn" Then
    For Each folder2 in fso.getFolder(fso.GetAbsolutePathName(folder)).SubFolders
      If folder2.Name <> ".svn" Then
        'WScript.Echo fso.GetAbsolutePathName(folder2)
        cleanApplicationFolder fso.GetAbsolutePathName(folder2)
      End If
    Next
  End If
Next


' Cleanups.

Set files      = Nothing
Set file       = Nothing
SET foldername = Nothing
Set folders    = Nothing
Set folder     = Nothing
Set folder2    = Nothing
Set fso        = Nothing
Set shell      = Nothing


Function debugOutputMissedName(text)
  If DebugOutputMissedNames = true Then
    WScript.Echo "Missed Folder: " & text
  End If
End Function

Function cleanApplicationFolder(root)
  s = root
  If fso.FolderExists(s) Then
    For Each file In fso.getFolder(s).Files
      If file.Name = "Makefile" Then
        DeleteFileOrFolder(file)
      End If
    Next
  Else
    debugOutputMissedName(s)
	Exit Function
  End If

  s = root & "\src"
  If fso.FolderExists(s) Then
    For Each file In fso.getFolder(s).Files
      If file.Name = "Makefile" Or _
         file.Name = "Makefile.Debug" Or _
         file.Name = "Makefile.Release" Then
        DeleteFileOrFolder(file)
      End If
    Next
  Else
    debugOutputMissedName(s)
	Exit Function
  End If

  s = root & "\src"
  If fso.FolderExists(s) Then
    For Each folder In fso.getFolder(root).SubFolders
      If folder.Name = "debug" Or folder.Name = "release" Then
        DeleteFileOrFolder(folder)
      End If
    Next
  Else
    debugOutputMissedName(s)
	Exit Function
  End If
End Function

' One central place to delete files and directories.

Sub DeleteFileOrFolder(byref obj)
  If DebugOutputDeletedNames = true Then
    WScript.Echo "Deleted: " & fso.GetAbsolutePathName(obj)
  End If

  On Error Resume Next
  'obj.Delete True

  On Error Goto 0                                ' System ist wieder für Fehler zuständig.
End Sub

