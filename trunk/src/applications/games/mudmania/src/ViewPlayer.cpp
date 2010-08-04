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

#include "ViewPlayer.h"
//#include "ConnectionHistory.h"

ViewPlayer::ViewPlayer(QWidget *parent /*=0*/)
 : View(parent)
{
  setObjectName(_("Player View"));
  //setHideTitle(true);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  m_editor.setFont(font);
  m_editor.setReadOnly(true);
  m_editor.setFrameStyle(QFrame::NoFrame);
  m_editor.setLineWrapMode(QTextEdit::NoWrap);
  m_editor.setWordWrapMode(QTextOption::NoWrap);
  m_editor.setUndoRedoEnabled(false);
  m_editor.setTabChangesFocus(true);

  m_fmt_output.setForeground(QBrush(QColor(0, 0, 255), Qt::SolidPattern));
  m_fmt_output.setFont(font);
  m_fmt_input.setForeground (QBrush(QColor(255, 0, 0), Qt::SolidPattern));
  m_fmt_input.setFont(font);
  m_fmt_input.setFontWeight(QFont::Bold);

  // into prefs

  m_editor.append(_("Welcome"));
  m_editor.append("\n\n");
  m_editor.insertPlainText(QString(_("Start:")) + " " + QDate::currentDate().toString(Qt::LocalDate) +
                                                  " " + QTime::currentTime().toString() +
                                                  " " + _("o'clock"));
  m_editor.insertPlainText("\n\n");

  //QVBoxLayout *main = new QVBoxLayout;
  //main->addWidget(m_editor);
  //main->setMargin(0);

  //setLayout(main);
  //??setWidget(&m_editor);

  //m_context = new JavaScriptContext(reinterpret_cast<MudMania *>(qApp)->runtime());

  m_thread = 0;
}

ViewPlayer::~ViewPlayer()
{
  //if (m_context) {
  //  qWarning() << "ViewPlayer::~ViewPlayer: context deleted.";
  //  delete m_context;
  //}
}

void ViewPlayer::connect(const QString &host, unsigned int port, const QString &username, const QString &password)
{
  m_host     = host;
  m_port     = port;
  m_username = username;
  m_password = password;

  m_thread = new ConnectionThread(this);

  QObject::connect(m_thread, SIGNAL(startedEventLoop()), this, SLOT(connectHost()));

  m_thread->start(QThread::HighPriority);

  qWarning() << "ViewPlayer::connect() fini = " << m_thread->isFinished() << "  running = " << m_thread->isRunning();

  // While starting our thread we emit a special signal to tell us, that all objects
  // are initialized and we are starting now the event loop. This allows us to work
  // with the thread's internal objects (e.g. m_telnet). We could use a mutex but a
  // simple signal does the same.

  // Do not call m_thread->connectHost() or m_thread->loginUser() here because the
  // thread is not initialized yet - just started. So we wait until we get the
  // signal which tells us that it's safe to go to the next step.
}

void ViewPlayer::connectHost()
{
  if (! m_thread)
    return;

  if (m_thread->connectHost(m_host, m_port)) {
    m_thread->loginUser(m_username, m_password);

    //ConnectionHistory::saveLogin(12321);
  }
}

void ViewPlayer::disconnect()
{
  if (! m_thread)
    return;

  qWarning() << "ViewPlayer::disconnect() fini = " << m_thread->isFinished() << "  running = " << m_thread->isRunning();

  m_thread->disconnectHost();
  m_thread->quit();

  //ConnectionHistory::saveLogout(12321);

  qWarning() << "Deleting thread !!!";
  delete m_thread; m_thread = 0;
}

void ViewPlayer::reconnect()
{
  m_thread->start(QThread::LowPriority);

  if (m_thread->connectHost()) {  // CHECK
    m_thread->loginUser();

    //ConnectionHistory::saveLogin(12321);
  }
}

void ViewPlayer::receiveText(const QString &text)
{
  insertText(text, 1);
}

// Called from MainWindow when new text was typed into the input widget.

void ViewPlayer::receiveInput(const QString &text)
{
  insertText(text, 2);

  emit sendText(text);
}

void ViewPlayer::cursorDown()
{
  QTextCursor cursor = m_editor.textCursor();

  cursor.clearSelection();
  cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);

  m_editor.setTextCursor(cursor);
}

void ViewPlayer::scrollDown()
{
  QScrollBar *sb;
  
  sb = m_editor.verticalScrollBar();
  if (sb)
    sb->setValue(sb->maximum());

  sb = m_editor.horizontalScrollBar();
  if (sb)
    sb->setValue(0);
}

void ViewPlayer::insertText(const QString &text, unsigned int type /*=0*/)
{
  cursorDown();

  QTextCursor cursor = m_editor.textCursor();

  switch (type) {
    case 1:
      cursor.insertText(text, m_fmt_output);
      break;

    case 2:
      cursor.insertText(text, m_fmt_input);
      break;

    default:
      cursor.insertText(text);
  }

  cursorDown();
  scrollDown();

  m_editor.ensureCursorVisible();
}

void ViewPlayer::insertImage(const QString &path)
{
  QTextCursor cursor = m_editor.textCursor();
  QTextImageFormat imageFormat;

  imageFormat.setName(path);               // e.g. ":/images/advert.png"
  cursor.insertImage(imageFormat);
}

QTextEdit *ViewPlayer::editor() const
{
  return const_cast<QTextEdit *>(&m_editor);
}

void ViewPlayer::runFile(const QString &filename)
{
  qWarning() << "ViewPlayer::runFile: executing script '" << filename << "'";

  //m_context->runFile(filename);
}


void ViewPlayer::runScript(const QString &data)
{
  qWarning() << "ViewPlayer::runScript: executing data '" << data << "'";

  ////m_context->runScript("var x=10.0; Math.sqrt(x*x*x*x);");
  //m_context->runScript(data.toLatin1());
}

