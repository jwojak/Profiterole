// fondaWin.cpp

#include "fondaWin.h"
#include <unistd.h>

fondaWin::fondaWin() : QWidget()
{
  QDesktopWidget dw;
  resize(dw.width()*0.7,dw.height()*0.7);
  std::cout<<this<<std::endl;
  
 
  imageWidget = new CVImageWidget(this);
  scrollArea = new imageScrollArea(this);
  headerTable = new  QTableWidget(this);
  scrollArea->move(280,40);
  headerTable->move(0,40);
  scrollArea->resize(dw.width()*0.5,dw.height()*0.5);
  customPlot = new QCustomPlot(this);
  customPlot->move(5,240);
  customPlot->resize(247,247);
  imageStatTable = new QTableWidget(this);
  imageStatTable->move(5, 500);

  QMenuBar *mainMenu = new QMenuBar( this );
  QMenu *fileMenu = mainMenu->addMenu("File");
  QMenu *imageMenu = mainMenu->addMenu("Image");
  QMenu *colorMapMenu = mainMenu->addMenu("ColorMap");
  QMenu *helpMenu = mainMenu->addMenu("Help");
  // IMAGE MENU ACTIONS !!
  QAction *backToOrigImageAct = new QAction("Show Original Image", this);
  QAction *gaussianFilterAct = new QAction("Gaussian Filter", this);
  QAction *medianFilterAct = new QAction("Median Filter", this);
  QAction *sobelFilterAct = new QAction("Sobel Filter", this);
  QAction *cannyEdgesAct = new QAction("Canny Edges", this);
  QAction *houghCircleAct = new QAction("Hough Circles",this);
  // FILE MENU ACTIONS !!
  QAction *openAct = new QAction("Open...", this);
  // HELP MENU ACTIONS !!
  QAction *helpAct = new QAction("Hi buddies !! this is ds10 ;)",this);
  // COLORMAP MENU ACTIONS !!
  QAction *linearGrayAct = new QAction("Linear Gray",this);
  QAction *cubeHelixAct = new QAction("CubeHelix", this);
  QAction *jetAct = new QAction("Jet", this);
  QAction *roulletAct = new QAction("Roullet", this);

 
 

  connect(scrollArea, SIGNAL(rescaleImageDynamiqSig(double, double)),imageWidget, SLOT(rescaleImageDynamiq(double, double)));

  helpMenu->addAction(helpAct);
  fileMenu->addAction(openAct);
  connect(openAct, SIGNAL(triggered()), this, SLOT(openDialogFile()));
  connect(this, SIGNAL(fileNameChanged()), this, SLOT(loadImage()));
  
  imageMenu->addAction(backToOrigImageAct);
  connect(backToOrigImageAct,SIGNAL(triggered()), this, SLOT(showOrigImage()));
  
  imageMenu->addAction(gaussianFilterAct);
  connect(gaussianFilterAct, SIGNAL(triggered()), this, SLOT(gaussianFilter()));

  imageMenu->addAction(medianFilterAct);
  connect(medianFilterAct, SIGNAL(triggered()), this, SLOT(medianFilter()));
  connect(this, SIGNAL(toggleToFilteredImage()), this, SLOT(showFilteredImage()));

  imageMenu->addAction(sobelFilterAct);
  connect(sobelFilterAct, SIGNAL(triggered()), this, SLOT(sobelFilter()));

  imageMenu->addAction(cannyEdgesAct);
  connect(cannyEdgesAct, SIGNAL(triggered()), this, SLOT(cannyFilter()));
  
  imageMenu->addAction(houghCircleAct);
  connect(houghCircleAct, SIGNAL(triggered()), this, SLOT(houghFilter()));
 
  colorMapMenu->addAction(linearGrayAct);
  colorMapMenu->addAction(cubeHelixAct);
  colorMapMenu->addAction(jetAct);
  colorMapMenu->addAction(roulletAct);

  QSignalMapper* signalMapper = new QSignalMapper(this);
  
  connect(linearGrayAct, SIGNAL(triggered()), signalMapper, SLOT(map()));
  connect(cubeHelixAct, SIGNAL(triggered()), signalMapper, SLOT(map()));
  connect(jetAct, SIGNAL(triggered()), signalMapper, SLOT(map()));
  connect(roulletAct, SIGNAL(triggered()), signalMapper, SLOT(map()));

  signalMapper->setMapping(linearGrayAct, 2);
  signalMapper->setMapping(cubeHelixAct, 3);
  signalMapper->setMapping(jetAct,4);
  signalMapper->setMapping(roulletAct,5);
  
  connect(signalMapper, SIGNAL(mapped(int)), imageWidget, SLOT(setColorMap(int)));
  
  


}

void fondaWin::gaussianFilter()
{
  cv::Size filterSize(15,15);
  cv::GaussianBlur(*matriceImage, *matriceImageFiltered, filterSize,15);
  emit toggleToFilteredImage();
}

void fondaWin::houghFilter()
{
  cv::vector<cv::Vec3f> circles;
  cv::HoughCircles(*matriceImage, circles, CV_HOUGH_GRADIENT, 2, 100);
  std::cout<<circles.size()<<std::endl;
  *matriceImageFiltered = matriceImage->clone();
   for( size_t i = 0; i < circles.size(); i++ )
    {
      cv::Point center(round(circles[i][0]), round(circles[i][1]));
      int radius = round(circles[i][2]);
      // draw the circle center
      cv::circle( *matriceImageFiltered, center, 3, cv::Scalar(255,255,255), -1, 8, 0 );
      // draw the circle outline
      cv::circle( *matriceImageFiltered, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }
   emit toggleToFilteredImage();
}

void fondaWin::medianFilter()
{ 
 
  cv::medianBlur(*matriceImage, *matriceImageFiltered, 3 );
  emit toggleToFilteredImage();
}

void fondaWin::cannyFilter()
{
  cv::Canny(*matriceImage, *matriceImageFiltered, 12.0, 50.0);
  emit toggleToFilteredImage();
}

void fondaWin::sobelFilter()
{
  cv::Sobel(*matriceImage, *matriceImageFiltered, -1,1,1);
  emit toggleToFilteredImage();    
}


void fondaWin::openDialogFile()
{
  
  this->fileName  = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.fits *.fit *.fts)");
  emit fileNameChanged();
}

void fondaWin::showFilteredImage()
{ 
  imageWidget->setMat(*matriceImageFiltered);
}

 void fondaWin::showOrigImage()
{
  imageWidget->setMat(*matriceImage);
}

void fondaWin::loadImage()
{ 
  if(!this->fileName.isNull())
    {
     
      std::auto_ptr<CCfits::FITS> pInfile(new CCfits::FITS(fileName.toStdString(),CCfits::Read,true));
    CCfits::PHDU& image = pInfile->pHDU(); 
    
    std::valarray<unsigned long>  contents;
        
    // read all user-specifed, coordinate, and checksum keys in the image
    image.readAllKeys(); 
    std::cout<<image.bitpix()<<std::endl;
     
    image.read(contents);
    long ax1(image.axis(0));
    long ax2(image.axis(1));
    std::cout<<ax1<<" "<<ax2<<std::endl;
    // create matrix to store image content

    switch(image.bitpix()) {
    case 8 :
      this->matriceImage = new cv::Mat(ax2, ax1, CV_8U);
      break;
    case -32 : // IEEE single precision floating point
      std::cout<<"Image format:: IEEE single precision floating point"<<std::endl;
      this->matriceImage = new cv::Mat(ax2, ax1, CV_32F);
      break;
    case -64 : // IEEE double precision point
      std::cout<<"Image format:: IEEE double precision floating point"<<std::endl;
      this->matriceImage = new cv::Mat(ax2,ax1, CV_64F);
    }

    this->matriceImageFiltered = new cv::Mat(ax2,  ax1, CV_8U);

    for (int j = 0; j<ax2; ++j)
      {
	for(int k=0; k<ax1 ; ++k)
	  {
	    this->matriceImage->at<float>(ax2-1-j,k) = contents[k+j*ax1];
	    
	  }	
	
      }
    // TEST POUR UN HISTOGRAMMe!!
    double maxIm = 0;
    cv::minMaxLoc(*matriceImage, 0, &maxIm, 0, 0);
    int histSize = maxIm;
    
    float range[] = {0,histSize};
    const float* histRange = {range};
    bool uniform = true; bool accumulate = false;
    cv::Mat im_hist;
    cv::calcHist(matriceImage, 1, 0, cv::Mat(), im_hist, 1, &histSize, &histRange, uniform, accumulate );
    std::cout<<"histogramme calcule!"<<std::endl;
    // FIN TEST POUR UN HISTOGRAMMe !!
    double maxVal = 1;
    cv::minMaxLoc(im_hist, 0, &maxVal, 0, 0);
    // generate some data:
    QVector<double> x(histSize), y(histSize); // initialize with entries 0..100
    for (int i=0; i<histSize; ++i)
      {
	x[i] = i; // x goes from -1 to 1
	y[i] = (im_hist.at<float>(i))/maxVal; // let's plot a quadratic function
	
      }
    // create graph and assign data to it:
   
    // TODO NE SURTOUT PAS LAISSER CES VALEURS EN DUR !!! C EST JUSTE POUR UN TEST  DE GRAPHIC !!
   
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, histSize);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
    
    imageStatTable->setRowCount(2);
    imageStatTable->setColumnCount(2);
   
    QTableWidgetItem *maxItem = new QTableWidgetItem();
    imageStatTable->setItem(0,0,maxItem);
    maxItem->setText("max");
    
    QTableWidgetItem *minItem = new QTableWidgetItem();
    imageStatTable->setItem(1,0,minItem);
    minItem->setText("min");



    QDesktopWidget dw;
    imageWidget->setMat(*matriceImage);
    // imageWidget->move(280,40);
    //scrollArea = new QScrollArea(this);
       //scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageWidget->getLabel());    
    // imageWidget->show();
    

    
    //get the keyword
    std::map< string, CCfits::Keyword * > & filesKeyword=image.keyWord();
     headerTable->setRowCount(filesKeyword.size());
     headerTable->setColumnCount(3);
    // headerTable = new QTableWidget(filesKeyword.size(),3,this);
  
    //show the content of the keyword map in a QtableWidget
    int cpt=0;
    for(std::map<std::string, CCfits::Keyword * >::iterator it=filesKeyword.begin(); it!=filesKeyword.end();++it){
      std::cout<<  it->first << " => " << *(it->second) << '\n';
      CCfits::Keyword * currentKW = it->second;
      float  v;float  a ;
      std::cout<<it->second->keytype()<<"--------"<<std::endl;
      if(it->second->keytype()<83 && it->second->keytype()>16)
	a = it->second->value(v);
      
      CCfits::ValueType r=it->second->keytype();
      std::stringstream ss;
      std::complex<float> v14(0,0);
      std::complex<float>  a14(0,0) ;
      std::complex<double> a15(0,0);
      std::complex<double> v15(0,0);
      std::string a4,v4;

      switch(r) 	{
      case CCfits::Tnull  : std::cout << "0\n"; break;
      case CCfits::Tbit : 
	std::cout << "1 \n";
	int  v1;int  a1 ;
	a1 = it->second->value(v1);
	ss << a1;
	break;
      case CCfits::Tbyte : 
	std::cout << "2 \n";
	int  v2;int  a2 ;
	a2 = it->second->value(v2);
	ss << a2;
	break;
      case CCfits::Tlogical : 
	std::cout << "3 \n";
	int  v3;int  a3 ;
	a3 = it->second->value(v3);
	ss << a3;
	break;
      case CCfits::Tstring : 
	std::cout << "4 \n";
	a4 = it->second->value(v4);
	ss << a4;
	break;
      case CCfits::Tushort :
	std::cout << "5 \n";
	int  v5;int  a5 ;
	a5 = it->second->value(v5);
	ss << a5;
	break;
      case CCfits::Tshort :  
	std::cout << "6 \n";
	int  v6;int  a6 ;
	a6 = it->second->value(v6);
	ss << a6;
	break;
      case CCfits::Tuint : 
	std::cout << "7 \n";
	int  v7;int  a7 ;
	a7 = it->second->value(v7);
	ss << a7;
	break;
      case CCfits::Tint :
	std::cout << "8 \n"; 
	int  v8;int  a8 ;
	a8 = it->second->value(v8);
	ss << a8;
	break;
      case CCfits::Tulong :
	std::cout << "9 \n"; 
	int  v9;int  a9 ;
	a9 = it->second->value(v9);
	ss << a9;
	break;
      case CCfits::Tlong : 
	std::cout << "10 \n"; 
	long int  v10;  long int  a10 ;
	a10 = it->second->value(a10);
	ss << a10;
	break;
      case CCfits::Tlonglong : 
	std::cout << "11 \n"; 
	long int  v11;long int  a11 ;
	a11 = it->second->value(a11);
	ss << a11;
	break;
      case CCfits::Tfloat :
	std::cout << "12 \n"; 
	float v12; float a12;
	a12 = it->second->value(v12);
	ss << a12; 
      case CCfits::Tdouble : 
	std::cout << "13 \n";
	float v13; float a13;
	a13 = it->second->value(v13);
	ss << a13;
      case CCfits::Tcomplex : 
	std::cout << "...14 \n"; 
	//a14 = it->second->value(v14);
	//ss << a14.real() <<" + i" << a14.imag();
	break;
      case CCfits::Tdblcomplex : std::cout << "15 \n";break;
	std::cout << "15 \n"; 
	a15 = it->second->value(v15);
	ss << a15.real() <<" + i" << a15.imag();
	break;
      case CCfits::VTbit: std::cout << "16 \n";break;
      case CCfits::VTbyte : std::cout << "17 \n";break;
      case CCfits::VTlogical : std::cout << "18 \n";break;
      case CCfits::VTushort : std::cout << "19 \n";break;
      case CCfits::VTshort : std::cout << "20 \n";break;
      case CCfits::VTuint : std::cout << "21 \n";break;
      case CCfits::VTint: std::cout << "22 \n";break;
      case CCfits::VTulong : std::cout << "23 \n";break;
      case CCfits::VTlong : std::cout << "24 \n";break;
      case CCfits::VTlonglong : std::cout << "25 \n";break;
      case CCfits::VTfloat : std::cout << "26 \n";break;
      case CCfits::VTdouble : std::cout << "27 \n";break;
      case CCfits::VTcomplex : std::cout << "28 \n";break;
      case CCfits::VTdblcomplex : std::cout << "29 \n";break;
      }						 
						 
      
      //std::cout<<"value tentative = " <<ss.str() << std::endl;
      QTableWidgetItem *currentItem = new QTableWidgetItem();
      headerTable->setItem(cpt,0,currentItem);
      currentItem->setText((it->first).c_str());
      if(r!=14){
      QTableWidgetItem *currentItem2 = new QTableWidgetItem();
      headerTable->setItem(cpt,1,currentItem2);
      currentItem2->setText((ss.str()).c_str());
      }
      cpt++;
    } 
       
    


    }

}
