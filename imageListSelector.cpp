// imageListSelector.cpp

#include "imageListSelector.h"

imageListSelector::imageListSelector() : QWidget()
{
  //imManager->getInstance();
 
}

imageListSelector::imageListSelector(QWidget *parent) : QWidget()
{
  imageListTable = new QTableWidget(this);
  imageListTable->setColumnCount(1);
}

void imageListSelector::buildListImageSelector()
{
  imagesManager *im =  imManager->getInstance();
  size_t nbImInList = im->nbImagesInList();
  imageListTable->setRowCount(nbImInList);

  std::cout<<"toto"<<std::endl;
  std::list<std::string> imagesNameList = im->getListImageNames();
  std::cout<<"titi"<<std::endl;
  int idxIm = 0;
  for(std::list<std::string >::iterator it=imagesNameList.begin(); it != imagesNameList.end(); ++it)
    { 
      QTableWidgetItem * item= new QTableWidgetItem(); 
      imageListTable->setItem (idxIm, 0,  item );
      item->setText(QString((*it).c_str()));
      idxIm++;
    }
}
