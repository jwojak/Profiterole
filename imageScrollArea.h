//imageScrollArea.h

#ifndef ____IMAGESCROLLAREA__H___
#define ____IMAGESCROLLAREA__H___

#include <QScrollArea>
#include <QMouseEvent>
#include <QPoint>
#include <QScrollBar>
#include <iostream> 
class imageScrollArea : public QScrollArea
{
  Q_OBJECT
  
    public:
  imageScrollArea();
  imageScrollArea(QWidget *parent=NULL);

  void mousePressEvent( QMouseEvent *event);
  void mouseMoveEvent( QMouseEvent *event);

 signals:
  void rescaleImageDynamiqSig(double a, double b); 
  void displayFlyingPosInImageSig(int x, int y);

 private:
  QPoint dragStartPosition;
  QPoint pointerClickPosInImage;
  QPoint pointerFlyingPosInImage;
  
};

#endif // ____IMAGESCROLLAREA__H___
