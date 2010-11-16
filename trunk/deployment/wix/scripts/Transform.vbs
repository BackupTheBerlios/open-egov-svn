' $Id$

Option Explicit

Dim installer, en_db, de_db

' It's very important to use this validation flag to ensure the transform
' can be applied to the original msi package later without any error.
Const msiTransformValidationNone = 1
Const msiTransformErrorNone = 0

Set installer = CreateObject("WindowsInstaller.Installer")
Set en_db = installer.opendatabase("en.msi", 0)
Set de_db = installer.opendatabase("de.msi", 0)
de_db.GenerateTransform en_db, "de.mst"
de_db.CreateTransformSummaryInfo en_db, "de.mst", msiTransformErrorNone, msiTransformValidationNone

Set installer = Nothing

