// $Id$

#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

#include <QDebug>

namespace OEG { namespace Math {

class Engine : public QObject
{
  Q_OBJECT

  public:
    Engine(QObject *parent = 0);
    virtual ~Engine();

    void clearEnvironment();
    QString compute(const QString &eq);

  protected:
    unsigned int parseEquation(const QString &eq);
    QString errorMessage() const;

  protected:
    QString      m_error_message;
    QStringList  m_history;
    QStringList  m_state;
};

}}

