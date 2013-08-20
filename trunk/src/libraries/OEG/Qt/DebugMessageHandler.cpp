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
#include <QtDebug>
#include <QFile>

#include <OEG/Qt/Application.h>
#include <OEG/Qt/DebugMessageHandler.h>
#include <OEG/Qt/MessageDialog.h>
#include <OEG/Qt/Settings.h>

#include <stdio.h>
#include <stdlib.h>

using namespace OEG::Qt;

// This is the message handling function which handles all text
// output. Here one may redirect the message to any stream. Write
// e.g. to a file or widget. Handles qDebug, qWarning, qCritical.
// The default message handler prints to the standard output (X11)
// or to the debugger (Windows). In case of a fatal message, the
// application aborts immediately. To restore the message handler,
// call qInstallMsgHandler(0).

void OEG_DebugMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &message)
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
  text.append(message);                                    // not: QString("%s").arg(message);

  if (true) { // send to debug window.
  }

  if (false) { // log into a file.
    QFile file("oeg-debug.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&file);
    ts << text << endl;
  }

  if (true) {  // console output.
    text += "\n";
    fprintf(stderr, text.toLocal8Bit().constData());
  }

  if (type == QtFatalMsg)
    abort();
}

