#ifndef __IMAGES_MANAGER_SINGLETON__
#define __IMAGES_MANAGER_SINGLETON__

#include <list>
#include "imageContainer.h"
#include <cstddef> // sinon utiliser nullptr a la place de NULL
#include <string> // passer a des qstring ??
#include <iostream>

#include <QObject>


class imagesManager : public QObject
{

 Q_OBJECT

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
  bool isSelectedImage(std::string);
  imageContainer* getFirstLoadedImage();
  size_t nbImagesInList();
  std::list<std::string> getListImageNames();

 signals:
  void changeOnImageList();
  void updateImaStats();
};

#endif //__IMAGES_MANAGER_SINGLETON_
