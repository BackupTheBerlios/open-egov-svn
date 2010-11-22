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

#include <QFileDialog>
#include <QMenuBar>
#include <QTextEdit>
#include <QToolBar>

#include <QApplication>
#include <QByteArray>
#include <QList>
#include <QString>

#include <QDebug>

#include <cmath>

#include "DirectoryEntry.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent /*=0*/)
 : OEG::Qt::MainWindow(parent)
{
  setWindowIcon(QIcon("icon.png"));

  m_text = new QTextEdit(this);
  m_text->setReadOnly(true);
  setCentralWidget(m_text);

  createAll();
}

MainWindow::~MainWindow()
{
  while (! m_dirs.isEmpty())
    delete m_dirs.takeFirst();
}

void MainWindow::createActions()
{
  OEG::Qt::MainWindow::createActions();

}

void MainWindow::createMenus()
{
  QMenu *menu;

  menu = menuBar()->addMenu(_("&File"));
  menu->addAction(standardAction(Open));
  menu->addSeparator();
  menu->addAction(standardAction(Exit));

  addHelpMenu();
}

void MainWindow::createToolBars()
{
  QToolBar *toolbar;

  toolbar = addToolBar(_("File"));
  toolbar->addAction(standardAction(Open));
  toolbar->addSeparator();
  toolbar->addAction(standardAction(Exit));
}

void MainWindow::standardActionOpen()
{
  m_file_name = QFileDialog::getOpenFileName(this, _("Open MSG File"), "", _("MSG Files (*.msg)"));

  while (! m_dirs.isEmpty())
    delete m_dirs.takeFirst();

  parseMessageFile(m_file_name);

}

void MainWindow::skipBytes(int bytes)
{
  m_file.read(bytes);
  //m_file.seek(m_file.pos() + bytes);
}

long long int MainWindow::readNumber(int bytes)
{
  QByteArray s = m_file.read(bytes);

  //qWarning() << "readNumber  bytes: " << bytes << " value: " << QString(s);

  return vbNumber(s);
}

long long int MainWindow::vbNumber(const QByteArray &s)
{
  unsigned char a, b, c, d, e, f, g, h;

  if (s.length() == 1) {
    a = s.at(0);

    switch (a) {
      case 255:
      case 254: return -1;
      case 253: return -2;
      case 252: return -3;
      case 251: return -4;
      default:
        return a;
    }
  }
  else if (s.length() == 2) {
    a = s.at(0);
    b = s.at(1);

    if ((a == 255) && (b == 255))
      return -1;
    else if ((a == 254) && (b == 255))
      return -1;
    else if ((a == 253) && (b == 255))
      return -2;
    else if ((a == 252) && (b == 255))
      return -3;
    else if ((a == 251) && (b == 255))
      return -4;
    else 
      return a + b * 256;
  }
  else if (s.length() == 4) {
    a = s.at(0);
    b = s.at(1);
    c = s.at(2);
    d = s.at(3);

    if ((a == 255) && (b == 255) && (c == 255) && (d == 255))
      return -1;
    else if ((a == 254) && (b == 255) && (c == 255) && (d == 255))
      return -1;
    else if ((a == 253) && (b == 255) && (c == 255) && (d == 255))
      return -2;
    else if ((a == 252) && (b == 255) && (c == 255) && (d == 255))
      return -3;
    else if ((a == 251) && (b == 255) && (c == 255) && (d == 255))
      return -4;
    else
      return a + b * 256 + c * 65536 + d * 16777216;
  }
  else if (s.length() == 8) {
    a = s.at(0);
    b = s.at(1);
    c = s.at(2);
    d = s.at(3);
    e = s.at(4);
    f = s.at(5);
    g = s.at(6);
    h = s.at(7);

    if ((b == 255) && (c == 255) && (d == 255) && (e == 255) && (f == 255) && (g == 255) && (h == 255)) {
      switch (a) {
        case 255:
        case 254: return -1;
        case 253: return -2;
        case 252: return -3;
        case 251: return -4;
      }
    }
    else
      return a                + b * 256             + c * 65536             + d * 16777216 +
             e * 4294967296LL + f * 1099511627776LL + g * 281474976710656LL + h * 72057594037927900LL;
  }

  return 0;
}

// Reads a number of characters from a particular sector in a file.
// Arguments: sect_size  The size of the sectors to be read
//            sid        The particluar sector to be read

QByteArray MainWindow::sectorReader(int sect_size, int sid)
{
  //int pos = m_file.pos();
  m_file.seek((sid * sect_size) + sect_size);

  return m_file.read(sect_size);  // Now read the sector itself.
}

void MainWindow::parseMessageFile(const QString &fileName)
{
  if (! QFile::exists(fileName)) {
    qWarning() << "File doesn't exist.";
    return;
  }

  m_file.setFileName(fileName);
  if (! m_file.open(QIODevice::ReadOnly)) {
    qWarning() << "File not open.";
    return;
  }

  if (m_file.fileName().right(4).toUpper() != ".MSG") {
    qWarning() << "File extension is not MSG.";
    return;
  }

  if (m_file.read(8) != QByteArray::fromHex("d0cf11e0a1b11ae1")) {   // Check if it is a compound file.
    qWarning() << "Wrong file signature.";
    return;
  }

  QString text;
  QByteArray ba;

  ba = m_file.read(20);                                              // Unique identifier with revision. 16 chars.
  qWarning() << "unique identifier: " << ba.toHex();

  if (m_file.read(2) != QByteArray::fromHex("feff")) {               // Check byte identifier.
    qWarning() << "Wrong byte identifier.";
    return;
  }

  int sector_size       = pow(2.0, readNumber(2));                   // Sector size.
  int short_sector_size = pow(2.0, readNumber(2));                   // Short sector size.

  skipBytes(10);                                                     // Read 10 chars of invalid data.

  int sectors_in_sat  = readNumber(4);                               // Number of SAT sectors.
  int dir_sid         = readNumber(4);                               // DIR SID.

  skipBytes(4);                                                      // Read 4 chars of invalid data.

  int min_stream_size = readNumber(4);                               // min stream size.
  int sid_ssat        = readNumber(4);                               // SID of the SSAT.
  int ssat_sectors    = readNumber(4);                               // Number of SSAT sectors.
  int msat_sid        = readNumber(4);                               // MSAT SID.
  int sect_msat       = readNumber(4);                               // Number of sectors in MSAT.

  qWarning() << "sector_size" << sector_size;
  qWarning() << "short_sector_size" << short_sector_size;
  qWarning() << "sectors_in_sat" << sectors_in_sat;
  qWarning() << "dir_sid" << dir_sid;
  qWarning() << "min_stream_size" << min_stream_size;
  qWarning() << "sid_ssat" << sid_ssat;
  qWarning() << "ssat_sectors" << ssat_sectors;
  qWarning() << "msat_sid" << msat_sid;
  qWarning() << "sect_msat" << sect_msat;

  QList<int> a_msat;
  QList<int> a_ssat;
  QByteArray ssat;
  int x, y, z;
  int i, j;

  for (i=1; i<110; i++) {                                            // Now read the first 109 entries in the MSAT.
    j = readNumber(4);                                               // Read 4 chars of MSAT sector IDs.

    if (j >= 0) {
      a_msat += j;
      qWarning() << "a_msat entry" << j;
    }
  }

  // The header has now been read. We now know quite a few things:
  // - The total number of sectors in the MSAT
  // - The first sector of the MSAT to start reading it
  // We can now read the MSAT and from there we can read everything.

  QByteArray string;
  if (msat_sid != -2) {                          // Do we need to read the MSAT if it are more than 109 entries?
    y = msat_sid;

    while (y >= 0) {                             // Lets loop through the MSAT.
      ba = sectorReader(sector_size, y);
 
      for (x=1; x<=(sector_size-4); x+=4) {      // For x=1 To sector_size-4 Step 4
        string = ba.mid(x-1, 4);
        int number = vbNumber(string);
        if (number > 0) {
          a_msat += number;
          qWarning() << "a_msat entry" << number;
        }
      }
 
      string = ba.right(4);
      if (vbNumber(string) > 0) {
        y = vbNumber(string);
      }
      else {
        y = -2;
      }
    }
  }

  text += "<h2>MSAT</h2>";
  text += "<p>";
  text += "a_msat.length: " + QString::number(a_msat.count()) + "<br>";
  for (x=0; x<a_msat.count(); x++) {                                 // For x=0 To MyArrayLen(a_msat,1)-1
    text += "data: " + QString::number(a_msat.at(x)) + "<br>";           // a_msat(x)
  }
  text += "</p>";

  ssat = "";                                     // We now have the MSAT hence we can now build the SAT from this.
  for (y=0; y<a_msat.count(); y++) {                       // For y=0 To (MyArrayLen(a_msat,1)-1)
qWarning() << "ssat: " << y << sector_size << a_msat.at(y);
    ssat += sectorReader(sector_size, a_msat.at(y));
  }

  text += "<h2>SAT</h2>";
  text += "<p>";
  text += "ssat.length: " + QString::number(ssat.length()) + "<br>";
  text += ssat.data();
  text += "</p>";
  text += "<p>";
  text += "data follows<br>";
  for (x=1; x<ssat.length(); x+=4) {          // For x=1 To Len(s_SAT) Step 4
    text += "Sector: " + QString::number(int(x/4)) +
            " Value: " + QString::number(vbNumber(ssat.mid(x-1, 4))) + "<br>";  // Mid(s_SAT,x,4)
  }
  text += "</p>";

  if (sid_ssat != -2) {                          // Now we can read the Short Sector SSAT.
    y = sid_ssat;

    ba = sectorReader(sector_size, y);

    for (x=1; x<=sector_size; x+=4) {           // For x=1 To sector_size Step 4
      string = ba.mid(x-1, 4);
      int number = vbNumber(string);
      if (number > 0) {
        a_ssat += number;
        qWarning() << "a_ssat entry" << number;
      }
    }

    qWarning() << "POS:" << __LINE__;

    z = 1;
    do {
      y = vbNumber(ssat.mid(y*4, 4));        // y=vbNumber(Mid(s_Sat,(y*4)+1,4))

      if (y > 0) {
        z++;   // Abbruchbedingung?
        ba = sectorReader(sector_size, y);

        for (x=1; x<=sector_size; x+=4) {   // For x=1 To sector_size Step 4
          string = ba.mid(x-1, 4);
          int number = vbNumber(string);
          if (number > 0) {
            a_ssat += number;
            qWarning() << "a_ssat entry" << number;
          }
        }
      }
    } while (z != ssat_sectors);
  }

  text += "<h2>SSAT</h2>";
  text += "<p>";
  text += "a_ssat.count: " + QString::number(a_ssat.count()) + "<br>";
  text += "<br>";
  text += "data follows<br>";
  for (x=0; x<a_ssat.count(); x++) {          // For M_X=0 To MyArrayLen(a_SSAT,1)-1
    text += "x: " + QString::number(x) +
            " Value: " + QString::number(a_ssat.at(x)) + "<br>";  // a_SSAT(M_X)
  }
  text += "</p>";

  qWarning() << "POS:" << __LINE__;

  y = dir_sid;                                   // Finally lets read the directory.
  z = -1;                                        // Lets loop through the directory.
  text += "<h2>DIRS</h2>";
  text += "<p>";
  while (y >= 0) {
    qWarning() << "POS:" << __LINE__;
    ba = sectorReader(sector_size, y);

    for (x=1; x<=sector_size; x+=128) {          // For x=1 To sector_size Step 128
      z++;

      // First lets check the type of the directory entry and if zero it is unused.
      if (vbNumber(ba.mid(x+66-1, 1)) != 0) {
        DirectoryEntry *e = new DirectoryEntry();
        int length = vbNumber(ba.mid(x+64-1,2));
        qWarning() << "L: " << length << ba.length();
        e->m_id                  = z;                                            // DID.       a_dir(0, MyArrayLen(a_dir,2)-1)
        e->m_name                = ba.mid(x-1, length).replace(QChar(0), "");    // Name.
        e->m_type                = vbNumber(ba.mid(x+ 66-1, 1));                 // Type.
        e->m_left_child          = vbNumber(ba.mid(x+ 68-1, 4));                 // DID Left Child.
        e->m_right_child         = vbNumber(ba.mid(x+ 72-1, 4));                 // DID Right Child.
        e->m_root_node           = vbNumber(ba.mid(x+ 76-1, 4));                 // DID root node.
        e->m_sid_of_first_sector = vbNumber(ba.mid(x+116-1, 4));                 // SID of first sector.
        e->m_stream_size         = vbNumber(ba.mid(x+120-1, 4));                 // Stream size.
        m_dirs << e;

        text += "DID: " + QString::number(e->m_id);
        text += " Name: " + e->m_name;
        text += " Type: " + QString::number(e->m_type);
        text += "<br>";
      }
    }

    y = vbNumber(ssat.mid(y*4, 4));     // vbNumber(Mid(s_Sat,(y*4)+1,4))
  }
  text += "</p>";


  //ba = m_file.read(8);
  //qWarning() << ba.toHex();

  m_text->setText("<h1>MSG-Viewer</h1>" + text);

  m_file.close();
}

