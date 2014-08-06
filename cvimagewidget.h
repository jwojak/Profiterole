#ifndef ___CVIMAGEWIDGET___
#define ___CVIMAGEWIDGET___

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <opencv2/opencv.hpp>

class CVImageWidget : public QWidget
{
   Q_OBJECT
 
   public:
   CVImageWidget(cv::Mat newMat, QWidget *parent = NULL);
   CVImageWidget(QWidget *parent = NULL);
   void setMat(const cv::Mat &newMat);
   cv::Mat getMat();
   QLabel*  getLabel();
   CVImageWidget operator=(cv::Mat m);
   
   private:
   cv::Mat _mat;
   QLabel* _label;
   void setLabel();

      signals:
public slots:
    
 
};

#endif //CVIMAGEWIDGET
