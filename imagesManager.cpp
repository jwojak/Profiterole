#include "imagesManager.h"

imagesManager *imagesManager::instance = NULL;


void imagesManager::addImageContainerInList(imageContainer* imaCont)
{
  std::cout<<"OHEHHEHEHEEH COUCOUC"<<std::endl;
  (this->imagesList).push_back(imaCont);
  emit changeOnImageList();
}

imageContainer* imagesManager::getLastContainedImageInList()
{
  return (this->imagesList).back();
}

imageContainer* imagesManager::getSelectedImage()
{
  std::cout<<"On vient aux selected apres!!"<<std::endl;
  std::cout<<"Parie qu'on echoue sur le isSeected"<<std::endl;
  for (std::list< imageContainer*>::iterator it = imagesList.begin();  it != imagesList.end(); ++it)
    {
      
      std::cout<< "isSel: "<<(*it)->isSelected()<<std::endl; 
      if((*it)->isSelected())
	{
	  return (*it);
	}
    }
  return NULL;
}

bool  imagesManager::isSelectedImage(std::string)
{
  return true;
}

std::list< std::string > imagesManager::getListImageNames()
{
  imageContainer* loadedImC = NULL;
  std::list< std::string > imageNameList;
  for (std::list< imageContainer* >::iterator it=imagesList.begin(); it != imagesList.end() ; ++it )
    {
      loadedImC = *it;
      imageNameList.push_back(loadedImC->getImageName());
    }
  return imageNameList;
}

imageContainer* imagesManager::getFirstLoadedImage()
{
  
  bool continueFor = true;
  imageContainer* loadedImC = NULL;
  for (std::list< imageContainer* >::iterator it=imagesList.begin(); it != imagesList.end() && continueFor; ++it)
    {
      if((*it)->isLoaded())
	{
	  loadedImC = *it;
	  continueFor = false;
	}
    }

  return loadedImC;
}

size_t imagesManager::nbImagesInList()
{
  return (this->imagesList).size();
}
// todo UN TRUC POUR RECUPERER L IMAGE CONTAINER!
