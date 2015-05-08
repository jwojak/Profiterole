// imageHeader.h

#ifndef ___IMAGEHEADER__H___
#define ___IMAGEHEADER__H___

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>

#include "imagesManager.h"

class imageHeader : public QTableWidget
{
  Q_OBJECT
 public:
  imageHeader();
  imageHeader(QWidget *parent=NULL);
//~imageHeader();

public slots:
void updateContent();

 private:
imagesManager *_imaManager;
};
#endif //___IMAGEHEADER__H___
