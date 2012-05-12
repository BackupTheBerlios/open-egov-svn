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

#include <QApplication>
#include <QTextStream>
#include <QDateTime>

#include <OEG/Qt/Application.h>
#include <OEG/Qt/DebugMessageHandler.h>
#include <OEG/Qt/MessageBox.h>
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

void OEG_DebugMessageHandler(QtMsgType type, const char *msg)
{
  switch (type) {
    case QtDebugMsg:
      fprintf(stderr, "Debug: %s\n", msg);
      break;
    case QtWarningMsg:
      fprintf(stderr, "Warning: %s\n", msg);
      break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s\n", msg);
      break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s\n", msg);
      abort();
    default: ;
  }
}

