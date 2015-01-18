// imageFilters.cpp

#include "imageFilters.h"

imageFilters::imageFilters():QWidget()
{
 
}

void imageFilters::prepareFilter()
{
  _imaManager = imagesManager::getInstance();   
  imageContainer *imC = _imaManager->getSelectedImage();
  cv::Mat *outputImageMatrix = new cv::Mat() ;
  *outputImageMatrix = (imC->getImageMatrix())->clone();
  //(imC->getImageMatrix())->copyTo(*outputImageMatrix);
  imageContainer *imFiltered = new imageContainer(outputImageMatrix,"filteredImage");
  _imaManager->addImageContainerInList(imFiltered);
}

void imageFilters::assignFilteredImageToMain()
{
  //fondaWin.setMatriceImageFiltered(this._outputImage); 
}

void imageFilters::sobelFilter()
{
  this->prepareFilter();
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = _imaManager->getLastContainedImageInList();
  cv::Sobel(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()),-1,1,1);
  emit filterExecutionDone(); 
}

void imageFilters::gaussianFilter()
{
  this->prepareFilter();
  cv::Size filterSize(15,15);
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = _imaManager->getLastContainedImageInList();
  cv::GaussianBlur(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()), filterSize,15);
  emit filterExecutionDone();
}

void imageFilters::medianFilter()
{
  this->prepareFilter();
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = _imaManager->getLastContainedImageInList();
  cv::medianBlur(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()), 3);
  emit filterExecutionDone();
}

void imageFilters::cannyFilter()
{
  this->prepareFilter();
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = _imaManager->getLastContainedImageInList();
  cv::Canny(*(imC_input->getImageMatrix()), *(imC_output->getImageMatrix()),12,.0, 50.0);
  emit filterExecutionDone();
}

void imageFilters::houghFilter()
{
  this->prepareFilter();
  imageContainer *imC_input = _imaManager->getSelectedImage();
  imageContainer *imC_output = _imaManager->getLastContainedImageInList();
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
  emit filterExecutionDone();
}
