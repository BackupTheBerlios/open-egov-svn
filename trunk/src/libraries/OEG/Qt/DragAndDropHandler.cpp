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

#include <OEG/Qt/DragAndDropHandler.h>

#include <QMimeData>
#include <QList>
#include <QStringList>
#include <QUrl>

#include <QDebug>

using namespace OEG::Qt;
using namespace Qt;

DragAndDropHandler::DragAndDropHandler(QObject *parent /*=0*/)
 : QObject(parent)
{
}

DragAndDropHandler::~DragAndDropHandler()
{
}

bool DragAndDropHandler::eventFilter(QObject *object, QEvent *event)
{
  Q_UNUSED(object);

  if (event->type() == QEvent::DragEnter)
    return dragEnter(static_cast<QDragEnterEvent *>(event));
  if (event->type() == QEvent::Drop)
    return drop(static_cast<QDropEvent *>(event));

  return false;
}

bool DragAndDropHandler::dragEnter(QDragEnterEvent *event)
{
  if (event->mimeData()->hasText()) {
    event->acceptProposedAction();
    return true; // Accept DnD.
  }

  return false;
}

bool DragAndDropHandler::drop(QDropEvent *event)
{
  const QMimeData *mimeData = event->mimeData();

  if (mimeData->hasText())
    qDebug() << event->mimeData()->text();

  if (mimeData->hasUrls()) {                     // A file or list of files.
    QStringList pathList;
    QList<QUrl> urlList = mimeData->urls();

    // Create list with local paths of all files.
    for (int i=0; i<urlList.size() && i<32; ++i) {
      pathList.append(urlList.at(i).toLocalFile());
    }

    //openAllFiles(pathList);
  }

  return true;
}

