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
      

      
      
      
       rescaleImageDynamiq(0.0,0.0);
      
   
    
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
   cv::Mat rgb;
   QPixmap p;
   QVector<QRgb> ctable;

   cv::minMaxLoc(_mat, &min, &max);
   
   std::cout<<"a = "<< a << " b = " << b << std::endl;
   min += a;
   max += b;
   std::cout<<"min = "<< min <<" max = "<<max<< std::endl;
   _mat.convertTo(_matToDisplay,CV_8U,255.0/(max-min),-min);
   std::cout<<"Super Super Toto"<<std::endl;
    cvtColor(_matToDisplay, rgb, CV_GRAY2RGB);

    for (int i=0; i<256; ++i)
      {
	//ctable.append(qRgb(i,0,0));
	// test pour construire la fameuse cubehelix LUT
	double start = 0.5;
	double hue = 1.0;
	double gamma = 1.0;
	double rots = -1.5;
	double pi =  3.14159265358979; // TODO dans la version finale utiliser un pi d'une lib de math!

	
	double fract =  static_cast<double>(i)/255.0;
	double angle = 2*pi*(start/3.0+1.0+rots*fract);
	fract = pow(fract,gamma);
	double amp = hue*fract*(1-fract)/2.0;
	
	double r = fract+amp*(-0.14861*cos(angle)+1.78277*sin(angle));
	double g = fract+amp*(-0.29227*cos(angle)-0.90649*sin(angle));
	double b = fract+amp*(1.97294*cos(angle));
	
	// on sature les negatifs
	r = r < 0.0 ? 0.0:r;
	g = g < 0.0 ? 0.0:g;
	b = b < 0.0 ? 0.0:b;
	// on sature aussi les positifs 
	r = r > 1.0 ? 1.0:r;
	g = g > 1.0 ? 1.0:g;
	b = b > 1.0 ? 1.0:b;

	  
	ctable.append(qRgb(round(r*255),round(g*255),round(b*255)));
      }
    
    QImage image(_matToDisplay.data, rgb.cols, rgb.rows, QImage::Format_Indexed8);
    image.setColorTable(ctable);
    p.convertFromImage(image);

       _label->setPixmap(p);
       resize(_mat.cols, _mat.rows);
 } 

