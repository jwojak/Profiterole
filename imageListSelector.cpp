// imageListSelector.cpp

#include "imageListSelector.h"

//imageListSelector::imageListSelector() : QWidget()
//{
  //imManager->getInstance();
 
//}

imageListSelector::imageListSelector(QWidget *parent) : QGroupBox(parent)
{
  
  qvbox = new QVBoxLayout(parent);
 
  this->setLayout(qvbox);
  this->setTitle("loaded images list");
}

void imageListSelector::updateContent()
{

  imagesManager *im =  imManager->getInstance();
  size_t nbImInList = im->nbImagesInList();
  //imageListTable->setRowCount(nbImInList);


  std::list<std::string> imagesNameList = im->getListImageNames();
  
  /*remove all radio button*/
  for(std::list<QRadioButton *>::iterator butIt=radioButtonList.begin(); butIt != radioButtonList.end(); ++butIt)
    {
      delete (*butIt);    
    }
  
  /*clean the list*/
  radioButtonList.clear();
  
  for(std::list<std::string >::iterator it=imagesNameList.begin(); it != imagesNameList.end(); ++it)
    { 
      QRadioButton *button = new QRadioButton(QString((*it).c_str()), this);  
     button->setCheckable(true);
     qvbox->addWidget(button);
     
     if(imManager->isSelectedImage(*it))
       {
	 button->setChecked(true);
	 connect(button,SIGNAL(clicked(bool)), this, SLOT(emitToggledTrue(bool)));
       }
     else
       {
	 connect(button,SIGNAL(clicked(bool)), this, SLOT(emitToggledFalse(bool)));
       }
     
     radioButtonList.push_back(button);   
    }
}

void imageListSelector::emitToggledFalse(bool)
{
  emit toggled(false);
}

void imageListSelector::emitToggledTrue(bool)
{
  emit toggled(true);
}
void imageListSelector::buildListImageSelector()
{
  
  imagesManager *im =  imManager->getInstance();
  size_t nbImInList = im->nbImagesInList();
  //imageListTable->setRowCount(nbImInList);


  std::list<std::string> imagesNameList = im->getListImageNames();
  
  /*remove all radio button*/
  for(std::list<QRadioButton *>::iterator butIt=radioButtonList.begin(); butIt != radioButtonList.end(); ++butIt)
    {
      delete (*butIt);    
    }
  
  /*clean the list*/
  radioButtonList.clear();
  
  for(std::list<std::string >::iterator it=imagesNameList.begin(); it != imagesNameList.end(); ++it)
    { 
      QRadioButton *button = new QRadioButton(QString((*it).c_str()), this);  
    
      qvbox->addWidget(button);
      if(imManager->isSelectedImage(*it))
	{
	  button->setChecked(true);
	}
      radioButtonList.push_back(button);   
    }
  
}
