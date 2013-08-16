// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
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

#include <QtCore>
#include <QtGui>

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>  // TODO: remove

#include "ViewEditor.h"

ViewEditor::ViewEditor(QWidget *parent /*=0*/)
 : View(parent)
{
  setObjectName("Editor View");
  //setHideTitle(true);

  m_editor = new QTextEdit();
  m_editor->setAcceptRichText(false);
  m_editor->setAutoFormatting(QTextEdit::AutoBulletList);

  setStandardFont();

  m_document = new QTextDocument(m_editor);
  m_cursor   = new QTextCursor(m_document);
  m_font     = new QFont();

  //setWidget(m_editor);

  setCurrentFile("");
}

void ViewEditor::openFileQuiet(const QString &fileName)
{
  loadFile(fileName);
}

void ViewEditor::setStandardFont()
{
  QFont font;

  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  m_editor->setFont(font);
}

bool ViewEditor::maybeSave()
{
  if (m_editor->document()->isModified()) {
    int ret = QMessageBox::warning(this, qApp->applicationName(),
                                   _("The document has been modified.\n"
                                     "Do you want to save your changes?"),
                                   QMessageBox::Yes | QMessageBox::Default,
                                   QMessageBox::No,
                                   QMessageBox::Cancel | QMessageBox::Escape);
    if (ret == QMessageBox::Yes)
      return save();
    else if (ret == QMessageBox::Cancel)
      return false;
  }

  return true;
}

void ViewEditor::loadFile(const QString &fileName)
{
  QFile file(fileName);

  if (! file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, qApp->applicationName(),
                         QString(_("Can't read file %1:\n%2."))
                         .arg(fileName)
                         .arg(file.errorString()));
    return;
  }

  //QTextStream in(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  //m_editor->setPlainText(in.readAll());
  m_editor->setPlainText(file.readAll());
  QApplication::restoreOverrideCursor();

  setCurrentFile(fileName);

  //statusBar()->showMessage(tr("File loaded"), 2000);
}

bool ViewEditor::saveFile(const QString &fileName)
{
  QFile file(fileName);

  if (! file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, qApp->applicationName(),
                         QString(_("Can't write file %1:\n%2."))
                         .arg(fileName)
                         .arg(file.errorString()));
    return false;
  }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  out << m_editor->toPlainText();
  QApplication::restoreOverrideCursor();

  setCurrentFile(fileName);

  //statusBar()->showMessage(tr("File saved"), 2000);

  return true;
}

void ViewEditor::setCurrentFile(const QString &fileName)
{
  m_filename = fileName;

  m_editor->document()->setModified(false);

  //setWindowModified(false);

  QString shownName;
  if (m_filename.isEmpty())
    shownName = "untitled.txt";
  else
    shownName = strippedName(m_filename);

  //setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(qApp->applicationName()));
}

QString ViewEditor::strippedName(const QString &fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}

void ViewEditor::newDocument()
{
  if (maybeSave()) {
    m_editor->clear();

    setCurrentFile("");
  }
}

void ViewEditor::open()
{
  if (maybeSave()) {
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, _("Open File"), "", /*fileFilter()*/ "");

    if (! fileName.isEmpty())
      loadFile(fileName);
  }
}

bool ViewEditor::save()
{
  if (m_filename.isEmpty())
    return saveAs();
  else
    return saveFile(m_filename);
}

bool ViewEditor::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this);

  if (fileName.isEmpty())
    return false;

  return saveFile(fileName);
}

// VIEW ACTIONS:

void ViewEditor::doEditZoomIn()
{
  m_editor->zoomIn(1);
}

void ViewEditor::doEditZoomNormal()
{
  setStandardFont();
}

void ViewEditor::doEditZoomOut()
{
  m_editor->zoomOut(1);
}

