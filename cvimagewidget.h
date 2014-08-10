#ifndef ___CVIMAGEWIDGET___
#define ___CVIMAGEWIDGET___

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QColor>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <sstream>
#include <string>
#include <fstream>

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
   cv::Mat _matToDisplay;
   QVector<QRgb> _ctable;
   QLabel* _label;
   void setLabel();
   void loadColorMap(std::string filename);


      signals:
public slots:
   void rescaleImageDynamiq(double a, double b);//should be private ?
   void setColorMap(int a); 
 
};

#endif //CVIMAGEWIDGET
