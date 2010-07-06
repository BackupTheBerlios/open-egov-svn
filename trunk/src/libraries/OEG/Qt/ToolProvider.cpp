// $Id$

#include <OEG/Qt/ToolProvider.h>

using namespace OEG::Qt;
using namespace Qt;

ToolProvider::ToolProvider(QWidget *parent /*=0*/, ::Qt::WindowFlags flags /*=0*/)
 : QWidget(parent, flags)
{
  setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

  resize(200, 110);
}

ToolProvider::~ToolProvider()
{
  if (m_tab_list.count() > 0) {

  }
}

