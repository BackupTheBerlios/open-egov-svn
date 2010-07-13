// $Id$

#include <OEG/Qt/Application.h>

#include <QProcess>

using namespace OEG::Qt;
using namespace Qt;

Application::Application(int &argc, char *argv[])
 : QApplication(argc, argv)
{
}

Application::~Application()
{
}

void Application::runComponent(const QString &cmd)
{
  runComponent(cmd, QStringList());
}

void Application::runComponent(const QString &cmd, const QStringList &arguments)
{
  QProcess process;

  process.setWorkingDirectory(QCoreApplication::applicationDirPath());
  process.startDetached(cmd, arguments);
}

