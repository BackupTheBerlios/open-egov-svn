' $Id$

' Script for MinGW/Windows environments to remove all temporary files
' without removing notes and additional files. Needed because it was
' not possible to automatically remove all object files and other
' generated files (which is required after bigger changes of certain
' OEG classes). This gets a "fresh" copy without the need to reimport
' virgin sources from SVN.
' If debugging is turned on (see Const section), maybe you should call
' the script from the command line: cscript path\cleanup.vbs

Option Explicit

Const DebugOutputDeletedNames = true
Const DebugOutputMissedNames  = true

' Initializations.

Dim shell: Set shell = WScript.CreateObject("WScript.Shell")
Dim fso: Set fso = CreateObject("Scripting.FileSystemObject")

Dim foldername, s, path
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

' Remove the "\.." from the foldername.
foldername = fso.GetAbsolutePathName(folder)

' Should contain the full directory name to the folder containing this script.
'Wscript.Echo foldername

DeleteFileOrFolderByPath(foldername & "\src\Makefile")
DeleteFileOrFolderByPath(foldername & "\src\applications\Makefile")
DeleteFileOrFolderByPath(foldername & "\src\libraries\Makefile")

s = foldername & "\src\libraries"
For Each folder In fso.getFolder(s).SubFolders
  If folder.Name <> ".svn" Then
    For Each folder2 in fso.getFolder(fso.GetAbsolutePathName(folder)).SubFolders
      If folder2.Name <> ".svn" Then
        cleanCppFolder fso.GetAbsolutePathName(folder2)
      End If
    Next
  End If
Next


s = foldername & "\src\applications"
For Each folder In fso.getFolder(s).SubFolders
  If folder.Name <> ".svn" Then
    For Each folder2 in fso.getFolder(fso.GetAbsolutePathName(folder)).SubFolders
      If folder2.Name <> ".svn" Then
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

Private Function FileNameMatches(ByVal name, ByVal pattern)
  If name = pattern Then FileNameMatches = True: Exit Function

  Dim splitpattern
  splitpattern = Split(pattern, "*")

  ' Look if array contains exactly 2 strings (left and right from "*").
  ' If so, compare the left one with left part of the name (equal size)
  ' and the right one with the right part. If both are the same this means
  ' the pattern matches the name.

  If UBound(splitpattern) = 1 Then
    If Len(name) >= Len(Join(splitpattern)) Then
      If splitpattern(0) = Left(name, Len(splitpattern(0))) And _
         splitpattern(1) = Right(name, Len(splitpattern(1))) Then
        FileNameMatches = True
        Exit Function
      End If
    End If
  End If

  FileNameMatches = False
End Function

Function cleanCppFolder(root)
  s = root
  If fso.FolderExists(s) Then
    For Each file In fso.getFolder(s).Files
      If FileNameMatches(file.Name, "object_script.*.Debug") Or _
         FileNameMatches(file.Name, "object_script.*.Release") Or _
         FileNameMatches(file.Name, "ui_*.h") Or _
         file.Name = "Makefile" Or _
         file.Name = "Makefile.Debug" Or _
         file.Name = "Makefile.Release" Then
        DeleteFileOrFolder(file)
      End If
    Next
    For Each folder In fso.getFolder(s).SubFolders
      If folder.Name = "debug" Or _
         folder.Name = "release" Then
        DeleteFileOrFolder(folder)
      End If
    Next
  Else
    debugOutputMissedName(s)
	Exit Function
  End If
End Function

Function cleanApplicationFolder(root)
  s = root
  If fso.FolderExists(s) Then
    For Each file In fso.getFolder(s).Files
      If file.Name = "Makefile" Then
        'DeleteFileOrFolder(file)
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
        'DeleteFileOrFolder(file)
      End If
    Next
    For Each folder In fso.getFolder(s).SubFolders
      If folder.Name = "debug" Or _
         folder.Name = "release" Then
        'DeleteFileOrFolder(folder)
      End If
    Next
  Else
    debugOutputMissedName(s)
	Exit Function
  End If
End Function

' One central place to delete files and directories.

Sub DeleteFileOrFolderByPath(ByRef path)
  On Error Resume Next

  If fso.FileExists(path) Then
    fso.DeleteFile path, true                    ' Keine Klammern.
  End If
  If fso.FolderExists(path) Then
    fso.DeleteFolder path, true
  End If

  On Error Goto 0                                ' System ist wieder für Fehler zuständig.
End Sub

Sub DeleteFileOrFolder(ByRef obj)
  path = fso.GetAbsolutePathName(obj)

  If DebugOutputDeletedNames = true Then
    'WScript.Echo "DeleteFileOrFolder: " & path
  End If

  DeleteFileOrFolderByPath(path)
End Sub

