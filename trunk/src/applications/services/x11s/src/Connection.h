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

#pragma once

#include <OEG/Common.h>

#include <QString>
#include <QDataStream>
#include <QDebug>

class QTcpSocket;
class Server;

class Connection : public QObject
{
  Q_OBJECT

  public:
    Connection(QTcpSocket *socket, Server *server);
    virtual ~Connection();

    bool    isValid();

    quint8  readByte();
    quint16 readShort();
    qint32  readInt();
    void    readOmit(int count);
    void    readByteOrder();
    void    flush();
    void    writeByte(quint8 data);
    void    writeShort(quint16 data);
    void    writeInt(qint32 data);
    void    writePaddingBytes(int count);
    void    writeReplyHeader(int argument);

  protected:
    quint8  countBits(quint32 data);
    int     sequenceNumber();

  signals:
    void disconnected(Connection *);

  private slots:
    void onReadyRead();
    void emitDisconnected();

  private:
    QTcpSocket             *m_socket;
    Server                 *m_server;
    QDataStream::ByteOrder  m_byte_order;
    int                     m_sequence_number;
};

