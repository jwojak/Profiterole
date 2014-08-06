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

       cv::Mat temp_mat;
       double min, max;
       cv::minMaxLoc(_mat, &min, &max);
       std::cout<<"---------------------------------------------------------"<<std::endl;
       std::cout<< " min = "<<min<<" |||||||||||| "<<" max = "<<max<<std::endl;   
       std::cout<<"---------------------------------------------------------"<<std::endl;
       _mat.convertTo(temp_mat,CV_8U,255.0/(max-min),-min);
       cvtColor(temp_mat, rgb, CV_GRAY2RGB);

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



