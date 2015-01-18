 #include "cvimagewidget.h"

 CVImageWidget::CVImageWidget(cv::Mat newMat, QWidget *parent) : QWidget(parent), _mat(newMat)
 {
   _label = new QLabel(this);
   setLabel();
   setColorMap(2);
   this->setMouseTracking(true);
 }


CVImageWidget::CVImageWidget(QWidget *parent) : QWidget(parent)
{
  _label = new QLabel(this);
  setLabel();
  setColorMap(2);
  
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
   this->setMouseTracking(true);
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
  

   cv::minMaxLoc(_mat, &min, &max);
   
   std::cout<<"a = "<< a << " b = " << b << std::endl;
   min += a;
   max += b;
   std::cout<<"min = "<< min <<" max = "<<max<< std::endl;
   _mat.convertTo(_matToDisplay,CV_8U,255.0/(max-min),-min);
   std::cout<<"Super Super Toto"<<std::endl;
    cvtColor(_matToDisplay, rgb, CV_GRAY2RGB);


    
    QImage image(_matToDisplay.data, rgb.cols, rgb.rows, QImage::Format_Indexed8);
    image.setColorTable(_ctable);
    p.convertFromImage(image);

       _label->setPixmap(p);
       resize(_mat.cols, _mat.rows);
 } 

void CVImageWidget::setColorMap(int a)
{
  std::cout<<"!!!!!!!!!!!!!!a = "<<a<<std::endl;
     if(_ctable.size()!=0)
	{
	  _ctable.erase(_ctable.begin(), _ctable.end());
	  std::cout<<"_ctable effacee, nouvelle taille =" <<_ctable.size()<<std::endl;
	}
  if(a==3) 
    {
   
      
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
	  
	  
	  _ctable.append(qRgb(round(r*255),round(g*255),round(b*255)));
	}
    }
  if(a==2)
    {
     
      for (int i=0; i<256; ++i)
	{
	  _ctable.append(qRgb(i,i,i));
	}
    }
  if(a==4)
    {
      loadColorMap("JET.rgb");
    }
  if(a==5)
    {
      loadColorMap("NCV_roullet.rgb");
    }
  // if(a==6)
  //  { TODO TOPO N EST PAS EN ENTIER!! IL  FAUT LE CHANGER AVANT!!
  //    loadColorMap("N");
  //  }
  setLabel();
}


void CVImageWidget::loadColorMap(std::string filename)
{
  std::ifstream colorfile(filename.c_str(), std::ifstream::in);
  //colorfile.open(filename, std::ifstream::in);
  int r,g,b;

  std::string line; 
  if(colorfile.is_open())
    {
     while(std::getline(colorfile, line))
       {
	 std::istringstream iss(line);
	 if ((iss >> r >> g >> b)) 
	   {
	     // std::cout<<"r = "<< r << " g = " << g << " b = " << b <<std::endl;
	   _ctable.append(qRgb(r,g,b));
	   } 
       }
    }
  colorfile.close();
}
