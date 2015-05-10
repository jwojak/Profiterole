// imageFilters.cpp

#include "imageFilters.h"

imageFilters::imageFilters():QWidget()
{
 _imaManager = imagesManager::getInstance();   
}

imageContainer *imageFilters::prepareFilter()
{
  //_imaManager = imagesManager::getInstance();   
  imageContainer *imC = _imaManager->getSelectedImage();
  cv::Mat *outputImageMatrix = new cv::Mat() ;
  *outputImageMatrix = (imC->getImageMatrix())->clone();
  //(imC->getImageMatrix())->copyTo(*outputImageMatrix);
  imageContainer *imFiltered = new imageContainer();
  imFiltered->setCVMat(outputImageMatrix,"filteredImage");
  // _imaManager->addImageContainerInList(imFiltered);
  return imFiltered;
}

void imageFilters::assignFilteredImageToMain()
{
  //fondaWin.setMatriceImageFiltered(this._outputImage); 
}

void imageFilters::sobelFilter()
{
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = this->prepareFilter();
  cv::Sobel(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()),-1,1,1);
  _imaManager->addImageContainerInList(imC_output);
  emit filterExecutionDone(); 
}

void imageFilters::gaussianFilter()
{
 
  cv::Size filterSize(15,15);
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = this->prepareFilter();
  cv::GaussianBlur(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()), filterSize,15);
  _imaManager->addImageContainerInList(imC_output);
  emit filterExecutionDone();
}

void imageFilters::medianFilter()
{
  
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = this->prepareFilter() ;
  cv::medianBlur(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()), 3);
  _imaManager->addImageContainerInList(imC_output);
  emit filterExecutionDone();
}

void imageFilters::cannyFilter()
{
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = this->prepareFilter();
  cv::Canny(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()),12,.0, 50.0);
  _imaManager->addImageContainerInList(imC_output);
  emit filterExecutionDone();
}

void imageFilters::houghFilter()
{
  this->prepareFilter();
  imageContainer *imC_input =  _imaManager->getSelectedImage();
  imageContainer *imC_output = this->prepareFilter();
  cv::vector<cv::Vec3f> circles;
  cv::HoughCircles(*(imC_input->getImageMatrix()), circles, CV_HOUGH_GRADIENT, 2, 100);
  for( size_t i = 0; i < circles.size(); i++ )
    {
      cv::Point center(round(circles[i][0]), round(circles[i][1]));
      int radius = round(circles[i][2]);
      // draw the circle center
      cv::circle( *(imC_output->getImageMatrix()), center, 3, cv::Scalar(255,255,255), -1, 8, 0 );
      // draw the circle outline
      cv::circle( *(imC_output->getImageMatrix()), center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }
  _imaManager->addImageContainerInList(imC_output);
  emit filterExecutionDone();
}
