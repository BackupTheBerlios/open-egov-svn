// $Id: MainWindow.h 223 2010-08-03 22:02:14Z gerrit-albrecht $
//
// Open eGovernment
// Copyright (C) 2005-2012 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <OEG/Common.h>

#include <QDialog>

#include "ui_about.h"

class AboutDialog : public QDialog, public Ui::AboutDialog
{
  Q_OBJECT

  public:
    AboutDialog(QWidget *parent = 0);

    void setInformationText();
    void setVersionText();

    void setLocalizedLicenseText(QString &text);

  protected:

  protected slots:
    void openUrl(const QUrl &link);

  private:
    QString   m_base_name;
    QString   m_application_name;
    QString   m_authors;
};

