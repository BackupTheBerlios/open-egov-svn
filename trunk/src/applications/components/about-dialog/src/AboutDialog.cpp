// $Id: Application.cpp,v 1.30 2007/05/30 18:40:31 gerrit Exp $
//
// G.A.S.I. Libraries Pack: Qt Extension Library
// Copyright (C) 2005-2008 by Gerrit M. Albrecht
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

#include <QUrl>
#include <QDesktopServices>

#include <OEG/Qt/Application.h>

#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent /*=0*/)
 : QDialog(parent)
{
  setupUi(this);

  QString headLine;

  headLine = qApp->organizationName();
  if (headLine.length() > 0)
    headLine += " ";
  headLine += qApp->applicationName();

  l_title->setText(headLine);

  setInformationText();
  setVersionText();

  m_tabs->setCurrentIndex(0);

  m_textbrowser_information->setOpenExternalLinks(true);

  connect(m_textbrowser_information, SIGNAL(anchorClicked(const QUrl &)),
          this,                      SLOT(openUrl(const QUrl &)));
}

void AboutDialog::setInformationText()
{
  QString str;

  str = "<html><body><p>";

  str += QString(_("The Open eGovenment Suite with its application \"%1\" is on the one hand "
           "an open source software project. "
           "You can always download the latest sources from the homepage at no cost. "
           "You may compile yourself the latest versions for free using free tools. "
           "Even the official binaries are available for free.")).arg(qApp->applicationName());

  str += "</p><p>";

  str += _("But then Open eGovernment is also a commercial product. If you find the software "
           "useful and if you would like to support the further development of this "
           "application, I kindly ask you to do so.");

  str += "</p><p>";

  str += _("There isn't a <em>better</em> commercial version. In fact, the registered version "
           "contains the same programs like the free version. After registration you may show "
           "your support with a logo at your websites, you can add your or your organization's name "
           "as supporter to this dialog, you get a registration number, your wishes will be "
           "implemented with a higher priority, ... Thats all.");
  str += "</p>";

  QString homepage = "test"; //dynamic_cast<Application *>(qApp)->homepage();

  if (homepage.length() > 0) {
    str += "<p>";
    str += _("Homepage of the project:");
    str += "<br><a href=\"" + homepage + "\">" + homepage + "</a></p>";
  }

  str += "</body></html>";

  m_textbrowser_information->setHtml(str);
}

void AboutDialog::setVersionText()
{
  QString str;

  str = "<html><body><p>";

  str += _("Version:");
  str += " " + qApp->applicationVersion() + "<br>";
  str += _("Build date:");
  str += " " + dynamic_cast<OEG::Qt::Application *>(qApp)->applicationBuildDate() + " " +
               dynamic_cast<OEG::Qt::Application *>(qApp)->applicationBuildTime() + "<br>";
  str += "</p>";

  //QString homepage = dynamic_cast<Application *>(qApp)->homepage();
  //str += "<p><a href=\"" + homepage + "version.php\">" + _("Check for Updates") + "</a>";
  //str += "</p>";
  str += "</body></html>";

  m_textbrowser_version->setHtml(str);
}

void AboutDialog::setLocalizedLicenseText(QString &text)
{
}

void AboutDialog::openUrl(const QUrl &link)
{
  bool rc = QDesktopServices::openUrl(link);

}

