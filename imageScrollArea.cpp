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
  
  if(event->button() == Qt::LeftButton)
    {
      QPoint clickPos = event->pos();
      std::cout<<"horizontalScrollBarValue = "<< this->horizontalScrollBar()->value()<<std::endl;
      std::cout<<"verticalScrollBarValue = " << this->verticalScrollBar()->value()<<std::endl;
      std::cout<<"click position in display = [" << clickPos.x() << "; "<< clickPos.y() << "]"<< std::endl;
      pointerClickPosInImage.setX(clickPos.x()+this->horizontalScrollBar()->value());
      pointerClickPosInImage.setY(clickPos.y()+this->verticalScrollBar()->value());
      emit displayFlyingPosInImageSig(clickPos.x() + this->horizontalScrollBar()->value(),clickPos.y() + this->verticalScrollBar()->value());
       
    }
  
  
  

}

void imageScrollArea::mouseMoveEvent(QMouseEvent *event)
{
  
  if(!(event->buttons()))
    {
      QPoint currentPos = event->pos();
      pointerFlyingPosInImage.setX(currentPos.x() + this->horizontalScrollBar()->value());
      pointerFlyingPosInImage.setY(currentPos.y() + this->verticalScrollBar()->value());
      // std::cout<<"toto"<<std::endl;
      emit displayFlyingPosInImageSig(currentPos.x() + this->horizontalScrollBar()->value(),currentPos.y() + this->verticalScrollBar()->value());
    }
  else if(!(event->buttons() & Qt::MiddleButton))
    {
      return;
    }
  else
    {
      std::cout<<"mouse current point = ("<< event->pos().x() <<", "<<event->pos().y() <<")"<<std::endl;
      std::cout<<"mouse starting point = ("<< dragStartPosition.x() <<", "<< dragStartPosition.y()<<")"<<std::endl;
      emit rescaleImageDynamiqSig(dragStartPosition.x()-event->pos().x(),dragStartPosition.y()-event->pos().y());
    }
}
