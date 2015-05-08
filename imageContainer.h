#ifndef __IMAGECONTAINER_H__
#define __IMAGECONTAINER_H__

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <string>
#include <QString>
#include <QVector>


class imageContainer
{
//  QOBJECT
 private:
  cv::Mat* _matriceImage;
  std::string _imageName;
  double _imaMin;
  double _imaMax;
  double _imaMean;
  double _imaStdDev;
  double _imaMedian;
  QVector<double> *_histogXbin;
  QVector<double> *_histogYVal;
  double _histogMaxVal;

  bool _isSelected;
  bool _isLoadedImage;
  std::map<QString, QString> *_headerContent;
 
 public:
 
  imageContainer(void);
  ~imageContainer(void);

  imageContainer(cv::Mat* matriceImage, std::string imageName);
 
  // imageContainer( cv::Mat *matriceImage, std::string imageName);
  //void setElement(cv::Mat &matriceImage, std::string imageName);
  void setHeaderContent(std::map<QString, QString> *hc);
  const std::map<QString, QString> * getHeaderContent() const; 
  
  cv::Mat* getImageMatrix();
  std::string getImageName();
  double getMedian();
  double getMean();
  double getStdDev();
  double getMin();
  double getMax();
  QVector<double>* getHistogXbin();
  QVector<double>* getHistogYVal();
  size_t getHistogBinMax();

  void renameImage(std::string newName);
  bool isSelected();
  bool isLoaded();
  void setLoadedOn();
  void setSelectOn();
  void setSelectOff();


};

#endif //__IMAGECONTAINER_H__
