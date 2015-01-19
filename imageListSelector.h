// imageListSelector.h

#ifndef ____IMAGELISTSELECTOR__H___
#define ____IMAGELISTSELECTOR__H___
 
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>

#include "imagesManager.h"
#include <iostream>
#include <string>
#include <list>

class imageListSelector : public QWidget
{
 Q_OBJECT

public:
 imageListSelector();
 imageListSelector(QWidget *parent=NULL);

public slots:
 void buildListImageSelector();

 private:
 imagesManager *imManager;
 QButtonGroup *buttonGroup;
 QTableWidget *imageListTable;
};


#endif //____IMAGELISTSELECTOR__H___
