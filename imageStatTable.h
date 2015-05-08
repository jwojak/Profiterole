// imageStatTable.h

#ifndef ___IMAGESTATTABLE__H___
#define ___IMAGESTATTABLE__H___

#include <QTableWidget>
#include "imagesManager.h"


class imageStatTable : public QTableWidget
{
  Q_OBJECT
  
 public:
  imageStatTable();
  imageStatTable(QWidget *parent =NULL);

  public slots:
    void updateContent();
    
 private: 
    imagesManager *_imaManager;
};

#endif // ___IMAGESTATTABLE__H___
