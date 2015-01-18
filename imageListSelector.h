// imageListSelector.h

#ifndef ____IMAGELISTSELECTOR__H___
#define ____IMAGELISTSELECTOR__H___
 
#include <QButtonGroup>
#include <QPushButton>

#include "imagesManager.h"
#include <iostream>
class imageListSelector : public QWidget
{
 Q_OBJECT

public:
 imageListSelector();
 imageListSelector(QWidget *parent=NULL);

private:
 imagesManager *imManager;
 QButtonGroup *buttonGroup;
};


#endif //____IMAGELISTSELECTOR__H___
