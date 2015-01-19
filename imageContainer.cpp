#include "imageContainer.h"

imageContainer::imageContainer()
{
  _isLoadedImage = false; //a faux par defaux, on met a true explicietement quand on charge une image avec le loader
}

imageContainer::~imageContainer()
{
  //delete this->_matriceImage;
this->_imageName = "NoName";
}




imageContainer::imageContainer(cv::Mat *matriceImage, std::string imageName)
{
  this->_matriceImage = matriceImage;
  this->_imageName = imageName;
}

cv::Mat* imageContainer::getImageMatrix()
{
  return this->_matriceImage;
}

std::string imageContainer::getImageName()
{
  return this->_imageName;
}

void imageContainer::renameImage(std::string newName)
{
  this->_imageName = newName;
}

bool imageContainer::isSelected()
{
  return this->_isSelected;
}

bool imageContainer::isLoaded()
{
  return this->_isLoadedImage;
}

void imageContainer::setLoadedOn()
{
  this->_isLoadedImage = true;
}

void imageContainer::setSelectOn()
{
  this->_isSelected = true;
}

void imageContainer::setSelectOff()
{
  this->_isSelected = false;
}
