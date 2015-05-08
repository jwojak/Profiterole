#include "imageContainer.h"
#include "iostream"

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
  
  cv::minMaxLoc(*matriceImage, &_imaMin, &_imaMax, 0, 0);
  cv::Mat meanIm0;
  cv::Mat stdDevIm0; 
  cv::meanStdDev(*matriceImage, meanIm0, stdDevIm0);
  
  _imaMean = meanIm0.at<double>(0,0);
  _imaStdDev = stdDevIm0.at<double>(0,0);
}

double imageContainer::getMedian()
{
  // MEDIAN NOT IMPLEMENTED YET TODO!!
  return 0.0;
}

double imageContainer::getMean()
{
  return this->_imaMean;
}

double imageContainer::getStdDev()
{
  return this->_imaStdDev;
}

double imageContainer::getMin()
{
  return this->_imaMin;
}

double imageContainer::getMax()
{
  return this->_imaMax;
}
//TODO FAIRE UN CONSTRUCTEUR PAR COPIE!

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

const std::map<QString, QString> *imageContainer::getHeaderContent() const
{
  return this->_headerContent;
}

void imageContainer::setHeaderContent(std::map<QString, QString> *hc)
{
  this->_headerContent = hc;
}
