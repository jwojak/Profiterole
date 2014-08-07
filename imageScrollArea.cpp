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
      emit rescaleImageDynamiqSig(65.0,65.0);
    }
}
