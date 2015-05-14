#ifndef ___IMAGEFILTERS_DS10___
#define ___IMAGEFILTERS_DS10___

#include <QApplication>
#include <QWidget>
// include opencv
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
// include c++
#include <iostream>

// mes include
#include "imagesManager.h"
#include "imageContainer.h"

class imageFilters : public QWidget
{

 Q_OBJECT
 
 public:
 imageFilters();
 // imageFilters(cv::Mat  &inputImage, cv::Mat &outputImage);
 
 public slots:
   void sobelFilter();
   void gaussianFilter();
   void medianFilter();
   void cannyFilter();
   void houghFilter();
   void assignFilteredImageToMain();
   
 signals:
   void filterExecutionDone();
  

 private:
   imageContainer * prepareFilter(std::string appliedFilterName);
   imagesManager *_imaManager;
};

#endif // ___IMAGEFILTERS_DS10___
