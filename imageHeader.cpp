#include "imageHeader.h"

imageHeader::imageHeader():QTableWidget()
{
  _imaManager = imagesManager::getInstance();
}

imageHeader::imageHeader(QWidget *parent) : QTableWidget(parent)
{
  _imaManager = imagesManager::getInstance();
}

void imageHeader::updateContent()
{
 
  imageContainer *curIma = _imaManager->getSelectedImage();
  // TODO REPLACER CE TEST PAR UNE ENCAPSULATION DANS UN TRY!
  if(curIma == NULL)
    {
      std::cout << "OHOHOHO" << std::endl;
    }
 
  const std::map<QString, QString> *imaHeader = curIma->getHeaderContent();
  //cleann tab if needed
  
  //resize the table
  this->setRowCount(imaHeader->size());
  this->setColumnCount(2);
  //populate new tab 
  size_t cpt = 0;
  for (std::map<QString,QString>::const_iterator it=imaHeader->begin(); it!=imaHeader->end(); ++it)
    {
      std::cout<< (it->first).toStdString() << " = " << (it->second).toStdString() << std::endl; 
      QTableWidgetItem *currentItem = new QTableWidgetItem();
      this->setItem(cpt,0,currentItem);
      currentItem->setText(it->first);
      QTableWidgetItem *currentItem2 = new QTableWidgetItem();
      this->setItem(cpt,1,currentItem2);
      currentItem2->setText(it->second); 
      cpt++;
    }
  
  //if empty map populate the tab with:
  // imaName
  // Nx 
  // Ny
}

