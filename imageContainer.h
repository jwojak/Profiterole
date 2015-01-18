#ifndef __IMAGECONTAINER_H__
#define __IMAGECONTAINER_H__

#include <opencv2/core/core.hpp>
#include <string>

class imageContainer
{
 private:
  cv::Mat* _matriceImage;
  std::string _imageName;
  bool _isSelected;
  bool _isLoadedImage;

 public:
 
  imageContainer(void);
  ~imageContainer(void);

  imageContainer(cv::Mat* matriceImage, std::string imageName);

  // imageContainer( cv::Mat *matriceImage, std::string imageName);
  //void setElement(cv::Mat &matriceImage, std::string imageName);
  
  cv::Mat* getImageMatrix();
  std::string getImageName();

  void renameImage(std::string newName);
  bool isSelected();
  bool isLoaded();
  void setLoadedOn();
  void setSelectOn();
  void setSelectOff();


};

#endif //__IMAGECONTAINER_H__
