#include "imagesManager.h"

imagesManager *imagesManager::instance = NULL;


void imagesManager::addImageContainerInList(imageContainer* imaCont)
{
  (this->imagesList).push_back(imaCont);
}

imageContainer* imagesManager::getLastContainedImageInList()
{
  return (this->imagesList).back();
}

imageContainer* imagesManager::getSelectedImage()
{
  return (this->imagesList).front();
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
