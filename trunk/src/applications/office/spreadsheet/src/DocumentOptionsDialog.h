// $Id$
//
// Spreadsheet
// Copyright (C) 2005-2007 by Gerrit M. Albrecht
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#ifndef SPREADSHEET_DOCUMENTOPTIONSDIALOG_H
#define SPREADSHEET_DOCUMENTOPTIONSDIALOG_H

#include <GASI/Common.h>

#include <QDialog>

#include "ui_document_options.h"

class DocumentOptionsDialog : public QDialog, public Ui::DocumentOptionsDialog
{
  Q_OBJECT

  public:
    DocumentOptionsDialog(QWidget *parent = 0);

  protected:

  private slots:

  private:

};

#endif

