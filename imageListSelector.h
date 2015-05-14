// imageListSelector.h

#ifndef ____IMAGELISTSELECTOR__H___
#define ____IMAGELISTSELECTOR__H___
 
#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>

#include "imagesManager.h"
#include <iostream>
#include <string>
#include <list>

class imageListSelector : public QGroupBox
{
 Q_OBJECT

public:
 //imageListSelector();
 imageListSelector(QWidget *parent=NULL);

public slots:
 void buildListImageSelector();
 void updateContent();
 void emitToggledFalse(bool );
 void emitToggledTrue(bool );

 signals:
   void toggle(bool);
   
 private:
 imagesManager *imManager;
 QVBoxLayout *qvbox;
 std::list<QRadioButton *> radioButtonList;
 //QButtonGroup *buttonGroup;
 //QTableWidget *imageListTable;
};


#endif //____IMAGELISTSELECTOR__H___
