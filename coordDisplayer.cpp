#include "coordDisplayer.h"
#include <sstream> 
#include <iostream>
#include <QString>
coordDisplayer::coordDisplayer(QWidget *parent)
{
}

void coordDisplayer::displayFlyingPosInImage(const int x, const int y)
{
  std::stringstream ss;
  ss << x;
  //  std::cout<<"emit??"<<std::endl;
  this->setText("Cursor Pos: [" + QString::number(x) + " ; " + QString::number(y) + "]" );
}

