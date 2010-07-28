// $Id$

#include <QtScript>
#include <QtCore>
#include <QtGui>

#include <QObject>
#include <QScriptValue>
#include <QScriptable>
#include <QScriptEngine>

#include <QApplication>
#include <QPushButton>

/*
http://tech-foo.blogspot.com/2008/05/how-to-make-c-classes-available-in.html
http://www.qtcentre.org/forum/f-qt-programming-2/t-using-enums-in-qtscript-9126.html
http://tech-foo.blogspot.com/2008/05/how-to-make-c-classes-available-in.html
http://tech-foo.blogspot.com/2008/05/qtscript-exposing-c-classes-part-two.html
http://www.qtcentre.org/forum/f-qt-programming-2/t-qtscript-17125.html
*/

int main (int argc, char *argv[])
{
  Q_UNUSED(argc)
  Q_UNUSED(argv)
  Q_INIT_RESOURCE(test);

  QApplication app(argc, argv);
  QPushButton button;

  QScriptEngine *engine = new QScriptEngine();
  QScriptValue go = engine->globalObject();

  QScriptValue script_button = engine->newQObject(&button);
  engine->globalObject().setProperty("button", script_button);

  engine->evaluate("button.text = 'Test'");
  engine->evaluate("button.styleSheet = 'font-style: italic'");
  engine->evaluate("button.styleSheet = 'background-color: yellow;' + button.styleSheet");
  engine->evaluate("button.show()");

  delete engine;

  return app.exec();
}

