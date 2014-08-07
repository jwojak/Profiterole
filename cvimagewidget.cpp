 #include "cvimagewidget.h"

 CVImageWidget::CVImageWidget(cv::Mat newMat, QWidget *parent) : QWidget(parent), _mat(newMat)
 {
   _label = new QLabel(this);
   setLabel();
 }

CVImageWidget::CVImageWidget(QWidget *parent) : QWidget(parent)
{
  _label = new QLabel(this);
  setLabel();
}

 void CVImageWidget::setMat(const cv::Mat &newMat)
 {
   _mat = newMat;
   setLabel();
 }

QLabel* CVImageWidget::getLabel()
{
  return _label;
}

 void CVImageWidget::setLabel()
 {
   if(_mat.cols*_mat.rows)
     {
       cv::Mat rgb;
       QPixmap p;

      
      
      
       rescaleImageDynamiq(0.0,0.0);
      
       cvtColor(_matToDisplay, rgb, CV_GRAY2RGB);

       p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows,rgb.cols*3, QImage::Format_RGB888));

       _label->setPixmap(p);
       resize(_mat.cols, _mat.rows);
    
       //resize(p.size());
     }
 }

cv::Mat CVImageWidget::getMat()
{
  return _mat;
}

CVImageWidget CVImageWidget::operator=(cv::Mat m)
{
  _mat = m;
}



void CVImageWidget::rescaleImageDynamiq(double a, double b)
 {  
   double min, max;
   cv::minMaxLoc(_mat, &min, &max);
   std::cout<<"min = "<< min <<" max = "<<max<< std::endl;
   std::cout<<"a = "<< a << " b = " << b << std::endl;
     
   _mat.convertTo(_matToDisplay,CV_8U,255.0/(max-min+a),-min+b);
   std::cout<<"Super Super Toto"<<std::endl;
 } 

