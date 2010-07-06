// $Id$

#include <OEG/Qt/MainWindow.h>
#include <OEG/Qt/ToolProvider.h>

using namespace OEG::Qt;
using namespace Qt;

MainWindow::MainWindow(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QMainWindow(parent, flags)
{
  m_tool_provider = new ToolProvider(this);
  m_tool_provider->show();
}

MainWindow::~MainWindow()
{
  if (m_tool_provider) {
    delete m_tool_provider; m_tool_provider = 0;
  }
}

