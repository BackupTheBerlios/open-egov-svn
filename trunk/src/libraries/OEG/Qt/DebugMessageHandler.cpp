// $Id$
//
// Open E-Government
// Copyright (C) 2005-2013 by Gerrit M. Albrecht
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

#include <QApplication>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

#include <QtDebug>
#include <QtGlobal>

#include <OEG/Qt/Application.h>
#include <OEG/Qt/DebugMessageHandler.h>
#include <OEG/Qt/MessageDialog.h>
#include <OEG/Qt/Settings.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace OEG::Qt;

// This is the message handling function which handles all text
// output. Here one may redirect the message to any stream. Write
// e.g. to a file or widget. Handles qDebug, qWarning, qCritical.
// The default message handler prints to the standard output (X11)
// or to the debugger (Windows). In case of a fatal message, the
// application aborts immediately. To restore the message handler,
// call qInstallMsgHandler(0).

void OEG_DebugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
  QString text = "";

  switch (type) {
    case QtDebugMsg:
      text = "Debug";
      break;
    case QtWarningMsg:
      text = "Warning";
      break;
    case QtCriticalMsg:
      text = "Critical";
      break;
    case QtFatalMsg:
      text = "Fatal";
      break;
  }

  text += ": ";
  text.append(message);                          // not: QString("%s").arg(message);

#ifdef _WIN32
  if (true) {                                    // Send to the Windows Debugger.
    OutputDebugString(reinterpret_cast<const wchar_t *>(text.utf16())); // Windows API.
  }
#endif

  if (false) {                                   // Log into a file.
    QFile file("oeg-debug.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&file);
    ts << text << endl;
  }

  if (true) {                                    // Console output.
    text += "\n";
    fprintf(stderr, text.toLocal8Bit().constData());
    //fprintf(stderr, "MESSAGE (%s:%u %s): %s\n", context.file, context.line,
    //        context.function, text.toLocal8Bit().constData());
    //fflush(stderr);
  }

  if (type == QtFatalMsg)
    abort();
}

