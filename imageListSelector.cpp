// imageListSelector.cpp

#include "imageListSelector.h"

imageListSelector::imageListSelector() : QWidget()
{
  //imManager->getInstance();
 
}

imageListSelector::imageListSelector(QWidget *parent) : QWidget()
{
  //imManager->getInstance();
  buttonGroup = new QButtonGroup(parent);
  size_t nbImInList = 3;//imManager->nbImagesInList();
  nbImInList = 3; //pour le test! 
  for(size_t idxIm = 0; idxIm < nbImInList; ++idxIm)
    {
      std::cout<<"on contruit le bouton"<<std::endl;
      QPushButton* button = new QPushButton("a", this );
      //button->setGeometry(QRect(QPoint(10, 10+10*idxIm), QSize(20, 20)));
      (this->buttonGroup)->addButton(button);
    }
}

