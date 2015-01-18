#ifndef __IMAGES_MANAGER_SINGLETON__
#define __IMAGES_MANAGER_SINGLETON__

#include <list>
#include "imageContainer.h"
#include <cstddef> // sinon utiliser nullptr a la place de NULL



class imagesManager
{

 private:
 imagesManager(){};
 ~imagesManager(){};

  static imagesManager *instance;
  std::list< imageContainer* > imagesList;

 public:
  static imagesManager* getInstance()
  {
    if(instance == NULL)
      {
	instance = new imagesManager();
      }
    return instance;
  }
  
  static void kill()
  {
    if(instance != NULL)
      {
	delete instance;
	instance = NULL;
      }
  }

  void addImageContainerInList( imageContainer *imaCont);
  imageContainer* getLastContainedImageInList();
  imageContainer* getSelectedImage();
  imageContainer* getFirstLoadedImage();
  size_t nbImagesInList();

};

#endif //__IMAGES_MANAGER_SINGLETON_
