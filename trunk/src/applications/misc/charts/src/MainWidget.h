// $Id:$

#ifndef OEG_DATA_DIAGRAMS_H
#define OEG_DATA_DIAGRAMS_H

#include <QString.h>

#include <QAxBindable.h>
#include <QTextEdit.h>
#include <QWidget.h>

class MainWidget : public QTextEdit // , public QAxBindable
{
  Q_OBJECT

  Q_CLASSINFO("ClassID",      "{AC1E7EF3-E310-421f-BD97-8EE77F03F9CA}")
  Q_CLASSINFO("InterfaceID",  "{5676AA5A-B5D4-4412-B166-FF1A9D6DBD2D}")
  Q_CLASSINFO("EventsID",     "{D2AE041C-DEFE-4648-85E4-B2D59E25A31F}")
  Q_CLASSINFO("Version",      "1.0")
  Q_CLASSINFO("Description",  "Open eGovernment: Chart")
  Q_CLASSINFO("ToSuperClass", "MainWidget")
  Q_CLASSINFO("StockEvents",  "yes")
  Q_CLASSINFO("Insertable",   "yes")
  //Q_CLASSINFO("RegisterObject", "yes")

  Q_PROPERTY(QString title READ title WRITE setTitle)

  public:
    MainWidget(QWidget *parent = 0, const char *name = 0);

    void setTitle(const QString &title);
    QString title() const;

    QString m_title;
};

#endif

