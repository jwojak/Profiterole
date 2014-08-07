//imageScrollArea.h

#ifndef ____IMAGESCROLLAREA__H___
#define ____IMAGESCROLLAREA__H___

#include <QScrollArea>
#include <QMouseEvent>
#include <iostream> 
class imageScrollArea : public QScrollArea
{
  Q_OBJECT
  
    public:
  imageScrollArea();
  imageScrollArea(QWidget *parent=NULL);

  void mousePressEvent( QMouseEvent *event);

 signals:
  void rescaleImageDynamiqSig(double a, double b); //todo passer des arguments
  
};

#endif // ____IMAGESCROLLAREA__H___
