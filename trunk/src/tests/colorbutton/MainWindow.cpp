// $Id$

#include <QtGui>

#include "MainWindow.h"
#include "ColorButton.h"

MainWindow::MainWindow()
 : QMainWindow(0)
{
  QWidget *w = new QWidget;
  setCentralWidget(w);

  QWidget *topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //QLabel *infoLabel = new QLabel("<i>xxx</i>");
  //infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  //infoLabel->setAlignment(Qt::AlignCenter);
  
  ColorButton *infoLabel = new ColorButton(QColor("#ffffff"));

  QWidget *bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->setMargin(5);
  vbox->addWidget(topFiller);
  vbox->addWidget(infoLabel);
  vbox->addWidget(bottomFiller);
  w->setLayout(vbox);


  setMinimumSize(160, 160);
}

