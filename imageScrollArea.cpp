// imageScrollArea.cpp

#include "imageScrollArea.h"

imageScrollArea::imageScrollArea() : QScrollArea()
{
}

imageScrollArea::imageScrollArea(QWidget *parent) : QScrollArea(parent)
{
}

void imageScrollArea::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::MiddleButton)
    { 
      dragStartPosition = event->pos();
      std::cout<<"mouse starting point = ("<< dragStartPosition.x() <<", "<< dragStartPosition.y()<<")"<<std::endl; 
     
    }
}

void imageScrollArea::mouseMoveEvent(QMouseEvent *event)
{
  if(!(event->buttons() & Qt::MiddleButton))
    return;
    
  std::cout<<"mouse current point = ("<< event->pos().x() <<", "<<event->pos().y() <<")"<<std::endl;
  std::cout<<"mouse starting point = ("<< dragStartPosition.x() <<", "<< dragStartPosition.y()<<")"<<std::endl;
  emit rescaleImageDynamiqSig(dragStartPosition.x()-event->pos().x(),dragStartPosition.y()-event->pos().y());
}
