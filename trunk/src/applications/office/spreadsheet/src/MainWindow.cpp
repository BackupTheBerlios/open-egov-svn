// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2011 by Gerrit M. Albrecht
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

#include <OEG/Qt/Application.h>
#include <OEG/Qt/TabWidget.h>
#include <OEG/Qt/MessageBox.h>

#include <QtGui>
#include <QtXml>
#include <QDomDocument>

#include "CommonOptionsDialog.h"
#include "DocumentOptionsDialog.h"
#include "DocumentPropertiesDialog.h"
#include "DocumentSecurityDialog.h"
#include "RenameTabDialog.h"

#include "CellTable.h"
#include "CellTableView.h"
#include "FunctionsDock.h"
#include "PropertiesDock.h"
#include "MainWindow.h"

MainWindow::MainWindow()
 : OEG::Qt::MainWindow(0) //, 500, 350)
{
  m_tabs = new OEG::Qt::TabWidget();
  if (! m_tabs)
    return;
//  m_tabs->addCloseTabButton(_("Close current tab."));
  m_tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_tabs->setTabShape(QTabWidget::Triangular);
  m_tabs->setTabPosition(QTabWidget::South);
  const_cast<QFont &>(m_tabs->font()).setPointSize(8);
  m_tabs->setElideMode(Qt::ElideNone);
  m_tabs->setContextMenuPolicy(Qt::CustomContextMenu);

  m_dock_properties = new PropertiesDock(this);
  addDockWidget(Qt::RightDockWidgetArea, m_dock_properties);

  action_insert_sheet();

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->setMargin(2);
  vbox->addWidget(m_tabs);
  setCentralLayout(vbox);

  //createActions();
  //createMenus();
  //createToolBars();
  createAll();

  setMinimumSize(200, 180);

  connect(m_tabs, SIGNAL(customContextMenuRequested(const QPoint &)),
          this,   SLOT(tabWidgetContextMenu(const QPoint &)));
  connect(m_tabs, SIGNAL(titleDoubleClicked(int)),
          this,   SLOT(tabWidgetTitleDoubleClicked(int)));
}

void MainWindow::action_file_load()
{
  QString filename;

  m_properties.setFilename("");
  filename = QFileDialog::getOpenFileName(this, _("Open File:"), ".", _("All Files (*);;XML Files (*.xml)"));

  if (filename.length() <= 0)
    return;

  loadDocument(filename);
}

void MainWindow::action_file_save()
{
  if (m_properties.filename().length() <= 0) {             // This is a bug!
    action_file_save_as();
    return;
  }

  saveDocument(m_properties.filename());
}

void MainWindow::action_file_save_as()
{
  QString filename = QFileDialog::getSaveFileName(this, _("Save File As:"), ".",
                                                  _("All Files (*);;XML Files (*.xml)"));
  if (filename.length() <= 0) {
    statusBar()->showMessage(_("No file name selected."), 2000);
    return;
  }

  if (! filename.endsWith(".xml"))
    filename += ".xml";

  saveDocument(filename);
}

void MainWindow::action_file_close()
{
  clearDocument();
}

void MainWindow::action_file_page_setup()
{
}

void MainWindow::action_file_print()
{
}

void MainWindow::action_file_print_preview()
{
}

void MainWindow::action_file_properties()
{
  DocumentPropertiesDialog *dialog = new DocumentPropertiesDialog(this);

  if (! dialog)
    return;

  dialog->m_edit_author->setText(m_properties.m_author);
  dialog->m_edit_company->setText(m_properties.m_company);

  if (dialog->exec() == QDialog::Accepted) {
    m_properties.m_author  = dialog->m_edit_author->text();
    m_properties.m_company = dialog->m_edit_company->text();
  }

  delete dialog;
}

void MainWindow::action_view_dock_functions()
{
}

void MainWindow::action_view_dock_properties()
{
}

void MainWindow::action_insert_rows()
{
}

void MainWindow::action_insert_columns()
{
}

void MainWindow::action_insert_sheet()
{
  CellTable *table = new CellTable(this);
  table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_tabs->addTab(table, _("Table") + QString(" ") + QString::number(m_tabs->count() + 1));
  m_tabs->setCurrentWidget(table);

  connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(tableCellClicked(int, int)));
  connect(table, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(tableItemClicked(QTableWidgetItem *)));

  connect(table, SIGNAL(itemClicked(QTableWidgetItem *)), m_dock_properties, SLOT(loadItemValues(QTableWidgetItem *)));
}

void MainWindow::action_insert_diagram()
{
}

void MainWindow::action_settings_common()
{
  CommonOptionsDialog *dialog = new CommonOptionsDialog(this);

  dialog->show();
}

void MainWindow::action_settings_document()
{
  DocumentOptionsDialog *dialog = new DocumentOptionsDialog(this);

  dialog->show();
}

void MainWindow::action_settings_security()
{
  DocumentSecurityDialog *dialog = new DocumentSecurityDialog(this);

  dialog->show();
}

void MainWindow::action_settings_view()
{
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

  //connect(m_action_file_load, SIGNAL(triggered()), this, SLOT(action_file_load()));
  //connect(m_action_file_save, SIGNAL(triggered()), this, SLOT(action_file_save()));

#if 0
  m_action_file_properties = new QAction(_("Properties ..."), this);
  m_action_file_properties->setStatusTip(_("Edit document properties."));
  connect(m_action_file_properties, SIGNAL(triggered()), this, SLOT(action_file_properties()));

  m_action_view_toolbar_edit = new QAction(_("Edit"), this);
  m_action_view_toolbar_edit->setStatusTip(_("Toggle edit toolbar."));
  m_action_view_toolbar_edit->setCheckable(true);
  connect(m_action_view_toolbar_edit, SIGNAL(triggered()), this, SLOT(viewToolbarEdit()));

  m_action_view_toolbar_format = new QAction(_("Format"), this);
  m_action_view_toolbar_format->setStatusTip(_("Toggle format toolbar."));
  m_action_view_toolbar_format->setCheckable(true);
  connect(m_action_view_toolbar_format, SIGNAL(triggered()), this, SLOT(viewToolbarFormat()));

  m_action_view_toolbar_widgets = new QAction(_("Widgets"), this);
  m_action_view_toolbar_widgets->setStatusTip(_("Toggle widgets toolbar."));
  m_action_view_toolbar_widgets->setCheckable(true);
  connect(m_action_view_toolbar_widgets, SIGNAL(triggered()), this, SLOT(viewToolbarWidgets()));

  m_action_view_toolbar_file = new QAction(_("File"), this);
  m_action_view_toolbar_file->setStatusTip(_("Toggle file toolbar."));
  m_action_view_toolbar_file->setCheckable(true);
  connect(m_action_view_toolbar_file, SIGNAL(triggered()), this, SLOT(viewToolbarFile()));

  m_action_view_statusbar = new QAction(_("StatusBar"), this);
  m_action_view_statusbar->setStatusTip(_("Toggle statusbar."));
  m_action_view_statusbar->setCheckable(true);
  connect(m_action_view_statusbar, SIGNAL(triggered()), this, SLOT(viewStatusBar()));

  m_action_view_dock_functions = new QAction(_("Functions"), this);
  m_action_view_dock_functions->setStatusTip(_("Toggle functions dock."));
  m_action_view_dock_functions->setCheckable(true);
  connect(m_action_view_dock_functions, SIGNAL(triggered()), this, SLOT(action_view_dock_functions()));

  m_action_view_dock_properties = new QAction(_("Properties"), this);
  m_action_view_dock_properties->setStatusTip(_("Toggle properties dock."));
  m_action_view_dock_properties->setCheckable(true);
  connect(m_action_view_dock_properties, SIGNAL(triggered()), this, SLOT(action_view_dock_properties()));

  m_action_view_full_screen = new QAction(_("&Full Screen"), this);
  m_action_view_full_screen->setShortcut(QKeySequence(_("Ctrl+F")));
  m_action_view_full_screen->setStatusTip(_("Toggle full screen mode."));
  connect(m_action_view_full_screen, SIGNAL(triggered()), this, SLOT(viewFullScreen()));

  m_action_view_zoom = new QAction(_("Zoom Level ..."), this);
  m_action_view_zoom->setStatusTip(_("Edit zoom level."));
  connect(m_action_view_zoom, SIGNAL(triggered()), this, SLOT(viewZoom()));


  m_action_settings_common = new QAction(_("Common ..."), this);
  m_action_settings_common->setStatusTip(_("Open the common settings dialog."));
  connect(m_action_settings_common, SIGNAL(triggered()), this, SLOT(action_settings_common()));

  m_action_settings_document = new QAction(_("Document ..."), this);
  m_action_settings_document->setStatusTip(_("Open the document settings dialog."));
  connect(m_action_settings_document, SIGNAL(triggered()), this, SLOT(action_settings_document()));

  m_action_settings_security = new QAction(_("Security ..."), this);
  m_action_settings_security->setStatusTip(_("Open the security settings dialog."));
  connect(m_action_settings_security, SIGNAL(triggered()), this, SLOT(action_settings_security()));

  m_action_settings_view = new QAction(_("View ..."), this);
  m_action_settings_view->setStatusTip(_("Open the view settings dialog."));
  connect(m_action_settings_view, SIGNAL(triggered()), this, SLOT(action_settings_view()));


  m_action_insert_rows = new QAction(_("Rows ..."), this);
  m_action_insert_rows->setStatusTip(_("Insert rows."));
  connect(m_action_insert_rows, SIGNAL(triggered()), this, SLOT(action_insert_rows()));

  m_action_insert_columns = new QAction(_("Columns ..."), this);
  m_action_insert_columns->setStatusTip(_("Insert columns."));
  connect(m_action_insert_columns, SIGNAL(triggered()), this, SLOT(action_insert_columns()));

  m_action_insert_sheet = new QAction(_("Table"), this);
  m_action_insert_sheet->setStatusTip(_("Insert table."));
  connect(m_action_insert_sheet, SIGNAL(triggered()), this, SLOT(action_insert_sheet()));

  m_action_insert_diagram = new QAction(_("Diagram"), this);
  m_action_insert_diagram->setStatusTip(_("Insert diagram."));
  connect(m_action_insert_diagram, SIGNAL(triggered()), this, SLOT(action_insert_diagram()));
#endif
}

void MainWindow::createMenus()
{
#if 0
  m_menu_file = menuBar()->addMenu(_("&File"));
  m_menu_file->addAction(m_action_file_load);
  m_menu_file->addAction(m_action_file_save);
  m_menu_file->addAction(m_action_file_save_as);
  m_menu_file->addAction(m_action_file_close);
  m_menu_file->addSeparator();
  m_menu_file->addAction(m_action_file_page_setup);
  m_menu_file->addAction(m_action_file_print);
  m_menu_file->addAction(m_action_file_print_preview);
  m_menu_file->addSeparator();
  m_menu_file->addAction(m_action_file_exit);

  m_menu_edit = menuBar()->addMenu(_("&Edit"));
  m_menu_edit->addAction(m_action_edit_undo);
  m_menu_edit->addAction(m_action_edit_redo);
  m_menu_edit->addSeparator();
  m_menu_edit->addAction(m_action_edit_cut);
  m_menu_edit->addAction(m_action_edit_copy);
  m_menu_edit->addAction(m_action_edit_paste);

  m_menu_view = menuBar()->addMenu(_("&View"));
  m_menu_view->addSeparator()->setText(tr("Alignment"));
  m_menu_view_toolbars = m_menu_view->addMenu(_("ToolBars"));
  m_menu_view_toolbars->addAction(m_action_view_toolbar_file);
  m_menu_view_toolbars->addAction(m_action_view_toolbar_format);
  m_menu_view_toolbars->addAction(m_action_view_toolbar_edit);
  m_menu_view_toolbars->addAction(m_action_view_toolbar_widgets);
  m_menu_view_docks = m_menu_view->addMenu(_("Docks"));
  m_menu_view_docks->addAction(m_action_view_dock_functions);
  m_menu_view_docks->addAction(m_action_view_dock_properties);

  m_menu_settings = menuBar()->addMenu(_("&Settings"));
  m_menu_settings->addAction(m_action_settings_common);
  m_menu_settings->addAction(m_action_settings_document);
  m_menu_settings->addAction(m_action_settings_security);
  m_menu_settings->addAction(m_action_settings_view);

  m_menu_insert = menuBar()->addMenu(_("&Insert"));
  m_menu_insert->addAction(m_action_insert_rows);
  m_menu_insert->addAction(m_action_insert_columns);
  m_menu_insert->addSeparator();
  m_menu_insert->addAction(m_action_insert_sheet);
  m_menu_insert->addAction(m_action_insert_diagram);

  menuBar()->addSeparator();

  m_menu_help = menuBar()->addMenu(_("&Help"));
  m_menu_help->addAction(m_action_about_me);
  m_menu_help->addAction(m_action_about_qt);
#endif
}

void MainWindow::createToolBars()
{
#if 0
  m_toolbar_file = addToolBar(_("File"));
  //m_toolbar_file->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  m_toolbar_file->addAction(m_action_file_load);
  m_toolbar_file->addAction(m_action_file_save);
  m_toolbar_file->addAction(m_action_file_save_as);
  m_toolbar_file->addAction(m_action_file_close);
  m_toolbar_file->addSeparator();
  m_toolbar_file->addAction(m_action_file_print);
  m_toolbar_file->addAction(m_action_file_print_preview);
  m_toolbar_file->addSeparator();
  m_toolbar_file->addAction(m_action_file_exit);

  m_toolbar_edit = addToolBar(_("Edit"));
  m_toolbar_edit->addAction(m_action_edit_undo);
  m_toolbar_edit->addAction(m_action_edit_redo);
  m_toolbar_edit->addSeparator();
  m_toolbar_edit->addAction(m_action_edit_cut);
  m_toolbar_edit->addAction(m_action_edit_copy);
  m_toolbar_edit->addAction(m_action_edit_paste);

  m_toolbar_format = addToolBar(_("Format"));

  m_toolbar_widgets = addToolBar(_("Widgets"));
#endif
}

void MainWindow::tabWidgetTitleDoubleClicked(int index)
{
  RenameTabDialog *dialog = new RenameTabDialog(this);

  if (! dialog)
    return;

  dialog->setText(m_tabs->tabText(index));

  if (dialog->exec() == QDialog::Accepted)
    m_tabs->setTabText(index, dialog->text());

  delete dialog;
}

void MainWindow::tabWidgetContextMenu(const QPoint &pos)
{
  //QMessageBox::warning(this, windowTitle(), QString("x=%1 y=%2").arg(pos.x()).arg(pos.y()));

  QList<QAction *> actions;

  // There are three different areas: the widget, the tabbar, and the free space of the tabwidget.

  if (false) { // (m_tabs->unprotectTabBar()->geometry().contains(pos)) {
    //actions.append(m_action_insert_sheet);
    //actions.append(m_action_file_properties); // Close sheet
  }
  else if (m_tabs->currentWidget()->geometry().contains(pos)) {
    //actions.append(m_action_file_print);
  }
  else {
    //actions.append(m_action_file_properties); // Close sheet
  }

  if (actions.count() > 0)
    QMenu::exec(actions, m_tabs->mapToGlobal(pos));
}

void MainWindow::tableCellClicked(int row, int column)
{
  //QMessageBox::warning(this, windowTitle(), QString("tc clicked"));
}

void MainWindow::tableItemClicked(QTableWidgetItem *item)
{
  //QMessageBox::warning(this, windowTitle(), QString("ti clicked"));

  //m_dock_properties->loadItemValues(item);
}

void MainWindow::loadDocument(const QString &filename)
{
  QFile file(filename);

  if (! file.open(QIODevice::ReadOnly)) {
    OEG::Qt::MessageBox::WarnMessage(QString(_("Can't read file %1:\n%2."))
                                     .arg(file.fileName()).arg(file.errorString()));
    return;
  }

  QByteArray content = file.readAll();
  file.close();

  QDomDocument doc;



  setCurrentFilename(filename);                            // Store current file name.
}

void MainWindow::saveDocument(const QString &filename)
{
  QFile file(filename);

  if (! file.open(QIODevice::WriteOnly)) {
    OEG::Qt::MessageBox::WarnMessage(QString(_("Can't write file %1:\n%2."))
                                     .arg(file.fileName()).arg(file.errorString()));
    return;
  }

  QDomDocument doc("GASI-Spreadsheet-ML");

  QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\"");
  doc.appendChild(header);

  QDomElement meta = doc.createElement("meta");
  QDomElement element = doc.createElement("author");
  QDomText text = doc.createTextNode("firstname lastname");
  element.appendChild(text);
  meta.appendChild(element);

  element = doc.createElement("date");
  text = doc.createTextNode(QDateTime::currentDateTime().toUTC().toString(Qt::ISODate));
  element.appendChild(text);
  meta.appendChild(element);
  doc.appendChild(meta);

  QDomElement tables = doc.createElement("tables");
  tables.setAttribute("current", QString::number(m_tabs->currentIndex()));
  tables.setAttribute("count", QString::number(m_tabs->count()));
  doc.appendChild(tables);

  QDomElement table, cell;
  for (int i=0; i<m_tabs->count(); i++) {
    table = doc.createElement("table");
    table.setAttribute("title", m_tabs->tabText(i));
    tables.appendChild(table);

    CellTable *celltable = (CellTable *) m_tabs->widget(i);  // noch haben wir nichts anderes

    int row, column;
    QTableWidgetItem *item;

    for (row=0; row<celltable->rowCount(); row++) {
      for (column=0; column<celltable->columnCount(); column++) {
        qWarning() << "row: " << row << " column: " << column;
        item = celltable->item(row, column);

        if (item) {
          cell = doc.createElement("cell");
          cell.setAttribute("row", QString::number(row));
          cell.setAttribute("column", QString::number(column));
          cell.setAttribute("value", item->text());
          table.appendChild(cell);
        }
      }
    }
  }

  QTextStream out(&file);                                  // Now save the DOM into a XML file.
  out << doc;
  file.close();
  doc.clear();

  setCurrentFilename(filename);                            // No errors, store this as new file name.
}

void MainWindow::clearDocument()
{
  setCurrentFilename("");

  CellTable *table = (CellTable *) m_tabs->currentWidget();
  table->clearContents();
}

void MainWindow::setCurrentFilename(const QString &filename)
{
  setWindowModified(false);
  m_properties.setFilename(filename);

  if (m_properties.filename().length() > 0) {
    setWindowTitle(filename + "[*]" + " - " + qApp->applicationName());
  }
  else {
    setWindowTitle(qApp->applicationName() + "[*]");
  }
}

