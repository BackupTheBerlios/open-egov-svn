// $Id$
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

#include <OEG/Qt/Application.h>
#include <OEG/Qt/TabbedMenuBar.h>

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QIcon>
#include <QTabWidget>
#include <QLabel>
#include <QLatin1String>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>

#include "PluginInterface.h"
#include "TextEditor.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  m_tabs = new OEG::Qt::TabWidget(this);
  if (! m_tabs) {
    qDebug() << "No tab widget.";
    return;
  }

  m_file_dialog_last_path = "";   // Save it on disk?

  m_tabs->setMovable(true);
  m_tabs->setDocumentMode(true);
  m_tabs->setTabsClosable(false);   // TODO: into config
  m_tabs->setUsesScrollButtons(true);
  m_tabs->separateCloseTabButton(_("Close Tab"));
  standardActionNew();
  m_tabs->setCurrentIndex(0);                              // Better use prefs.

  setCentralWidget(m_tabs);

  activateWindow();

  createAll();

  loadPlugins();
  loadFileTypes();
}

MainWindow::~MainWindow()
{
  if (m_tabs) {
    delete m_tabs; m_tabs = 0;
  }
}

void MainWindow::updateStatusBar()
{
  if (! currentEditor()) {
    qDebug() << "MainWindow::updateStatusBar(): no editor object.";
    return;
  }

  m_sb_number_of_lines->setText(_("Lines:") + QLatin1String(" ") + QString::number(currentEditor()->lineCount()));
  m_sb_current_row->setText(_("Row:") + QLatin1String(" ") + QString::number(0));
  m_sb_current_column->setText(_("Col:") + QLatin1String(" ") + QString::number(0));
  m_sb_overwrite_mode->setText((currentEditor()->overwriteMode()) ? _("INS") : _("OWR"));
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createStatusBar()
{
  m_sb_number_of_lines = new QLabel("Lines: 0000");
  m_sb_number_of_lines->setMinimumSize(m_sb_number_of_lines->sizeHint());
  m_sb_number_of_lines->setAlignment(Qt::AlignCenter);
  m_sb_number_of_lines->setToolTip(_("The number of text lines."));
  statusBar()->addPermanentWidget(m_sb_number_of_lines);

  m_sb_current_row = new QLabel("Row: 0000");
  m_sb_current_row->setMinimumSize(m_sb_current_row->sizeHint());
  m_sb_current_row->setAlignment(Qt::AlignCenter);
  m_sb_current_row->setToolTip(_("Current row of the cursor."));
  statusBar()->addPermanentWidget(m_sb_current_row);

  m_sb_current_column = new QLabel("Col: 0000");
  m_sb_current_column->setMinimumSize(m_sb_current_column->sizeHint());
  m_sb_current_column->setAlignment(Qt::AlignCenter);
  m_sb_current_column->setToolTip(_("Current column of the cursor."));
  statusBar()->addPermanentWidget(m_sb_current_column);

  m_sb_overwrite_mode = new QLabel("XXX");
  m_sb_overwrite_mode->setMinimumSize(m_sb_overwrite_mode->sizeHint());
  m_sb_overwrite_mode->setAlignment(Qt::AlignRight);
  m_sb_overwrite_mode->setToolTip(_("Tells, if insert or overwrite mode."));
  statusBar()->addPermanentWidget(m_sb_overwrite_mode);

  OEG::Qt::MainWindow::createStatusBar();

  updateStatusBar();
}

void MainWindow::createDockWidgets()
{
}

void MainWindow::createMenus()
{
  QMenu *menu;

  menu = getStandardMenu(FileMenu);
  menu->addAction(standardAction(New));
  menu->addAction(standardAction(Open));
  menu->addAction(standardAction(Reload));
  menu->addAction(standardAction(Save));
  menu->addAction(standardAction(SaveAs));
  menu->addAction(standardAction(Close));
  menu->addSeparator();
  menu->addAction(standardAction(Print));
  menu->addAction(standardAction(PrintPreview));
  menu->addAction(standardAction(PrintSettings));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  menu = getStandardMenu(EditMenu);
  menu->addAction(standardAction(Undo));
  menu->addAction(standardAction(Redo));
  menu->addSeparator();
  menu->addAction(standardAction(Cut));
  menu->addAction(standardAction(Copy));
  menu->addAction(standardAction(Paste));
  menu->addSeparator();
  menu->addAction(standardAction(SelectAll));
  menu->addSeparator();
  menu->addAction(standardAction(Delete));

  QMenu *extensionsMenu = menuBar()->addMenu(_("E&xtensions"));
  extensionsMenu->addAction("Test");

  addStandardMenu(HelpMenu);
}

void MainWindow::createToolBars()
{
  QAction  *action;
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(New));
  toolbar->addAction(standardAction(Open));
  toolbar->addAction(standardAction(Save));
  toolbar->addAction(standardAction(SaveAs));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Undo));
  toolbar->addAction(standardAction(Redo));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Cut));
  toolbar->addAction(standardAction(Copy));
  toolbar->addAction(standardAction(Paste));
  toolbar->addAction(standardAction(Delete));
}

void MainWindow::createTabbedMenuBar()
{
}

void MainWindow::loadPlugins()
{
  QString baseName = applicationBaseName();
  QDir pluginsDir(qApp->applicationDirPath(), "*.dll;*.so");  // Ignore .a files.

  if (pluginsDir.dirName().toLower() == "bin")
    pluginsDir.cdUp();
  pluginsDir.cd("plugins/" + baseName);

  qDebug() << "Loading Plugins from: " << pluginsDir.absolutePath();

  PluginInterface *pluginAPI;  // Do not name it "interface".
  QObject *plugin;

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    plugin = pluginLoader.instance();
    if (plugin) {
      pluginAPI = qobject_cast<PluginInterface *>(plugin);
      if (pluginAPI) {
        if (pluginAPI->pluginApplicationName() != baseName) {
          qWarning() << "Application base names from plugin and application do not match:";
          qWarning() << " plugin file name:" << fileName;
          qDebug() << " application base name:" << baseName;
          qDebug() << " plugin application name:" << pluginAPI->pluginApplicationName();
        }
        else {
          m_plugins.append(pluginAPI);
        }
      }
    }
    else {
      qDebug() << "Plugin not found: " << fileName;
    }
  }

  qDebug() << "Number of Plugins found: " << m_plugins.count();
}

void MainWindow::loadFileTypes()
{
}

void MainWindow::standardActionNew()
{
  TextEditor *editor = new TextEditor(this);

  if (! editor)
    return;

  editor->highlightCurrentLine();
  editor->setLineNumbersWidth(-1);
  editor->showLineNumbers();

  connect(editor,                 SIGNAL(textChanged()),
          this,                   SLOT(updateStatusBar()));
  connect(editor,                 SIGNAL(cursorPositionChanged()),
          this,                   SLOT(updateStatusBar()));
  connect(editor,                 SIGNAL(copyAvailable(bool)),
          standardAction(Cut),    SLOT(setEnabled(bool)));
  connect(editor,                 SIGNAL(copyAvailable(bool)),
          standardAction(Copy),   SLOT(setEnabled(bool)));
  connect(editor,                 SIGNAL(copyAvailable(bool)),
          standardAction(Delete), SLOT(setEnabled(bool)));
  connect(editor,                 SIGNAL(undoAvailable(bool)),
          standardAction(Undo),   SLOT(setEnabled(bool)));
  connect(editor,                 SIGNAL(redoAvailable(bool)),
          standardAction(Redo),   SLOT(setEnabled(bool)));

  m_tabs->addTab(editor, _("Unnamed"));

  m_tabs->setCurrentIndex(m_tabs->count()-1);

  currentEditor()->setFocus();
}

void MainWindow::standardActionOpen()
{
  bool        documentOpened = false;
  QStringList files = QFileDialog::getOpenFileNames(this, _("Open a text file"), m_file_dialog_last_path);
  QString     filePathWithName;

  for (int i = 0; i < files.size(); i++) {
    filePathWithName = files.at(i);

    qDebug() << "File name:" << filePathWithName;

    if (! filePathWithName.isNull()) {
      QFileInfo fi(filePathWithName);

      QString extension = fi.completeSuffix();
      QString fileName  = fi.fileName();

      m_file_dialog_last_path = fi.canonicalPath();        // Store path for the next time.

      QFile file(filePathWithName);
      if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray text = file.readAll();

        standardActionNew();
        TextEditor *editor = currentEditor();
        editor->insertPlainText(text.constData());
        editor->setDocumentTitle(fileName);
        editor->textCursor().movePosition(QTextCursor::Start);
        
        m_tabs->setTabText(m_tabs->currentIndex(), fileName);
        m_tabs->setTabToolTip(m_tabs->currentIndex(), filePathWithName);
        m_tabs->setTabWhatsThis(m_tabs->currentIndex(), "xxx");

        documentOpened = true;                             // We opened a new document.
      }
    }
  }

  // If count of tabs is greater than 1 and the first tab is _("Unnamed")
  // and unchanged/empty, then remove the first tab.

  if ((m_tabs->count() > 1) && (documentOpened)) {
    if (m_tabs->tabBar()->tabText(0) == _("Unnamed")) {
      TextEditor *editor = dynamic_cast<TextEditor *>(m_tabs->widget(0));
	  if (editor) {
        if (! editor->document()->isModified()) {
          m_tabs->removeTab(0);
          delete editor; editor = 0;
        }
      }
//editor->document()->characterCount()
//editor->document()->blockCount()
//tabBar()->setTabTextColor(int index, const QColor & color)
    }
  }
}

void MainWindow::standardActionClose()
{
  m_tabs->closeTab();
}

void MainWindow::standardActionPrint()
{
}

TextEditor *MainWindow::currentEditor() const
{
  if (! m_tabs)
    return 0;

  QWidget *w = m_tabs->currentWidget();
  if (! w)
    return 0;

  return dynamic_cast<TextEditor *>(w);
}

