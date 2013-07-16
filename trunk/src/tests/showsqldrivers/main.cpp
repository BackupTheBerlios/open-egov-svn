// $Id$

#include <QCoreApplication>
#include <QtSQL>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  qDebug() << QSqlDatabase::drivers();
  return 0;
}

