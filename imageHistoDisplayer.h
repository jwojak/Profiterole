// imageHistoDisplayer.h

#ifndef ___IMAGEHISTOGDISPLAYER__H___
#define ___IMAGEHISTOGDISPLAYER__H___
 
#include "qcustomplot.h" 
#include "imagesManager.h"

class imageHistoDisplayer : public QCustomPlot
{
  Q_OBJECT

 public:
  imageHistoDisplayer();
  imageHistoDisplayer(QWidget *parent=NULL);
  
  public slots:
    void updateContent(); 

 private:
    imagesManager *_imaManager;
};

#endif// ___IMAGEHISTOGDISPLAYER__H___
