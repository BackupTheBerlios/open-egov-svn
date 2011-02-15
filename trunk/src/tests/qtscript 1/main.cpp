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

