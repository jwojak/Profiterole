// fondaWin.cpp

#include "fondaWin.h"
#include <unistd.h>

fondaWin::fondaWin() : QWidget()
{
  QDesktopWidget dw;
  QGridLayout *grille = new QGridLayout(this);
 
  resize(dw.width()*0.7,dw.height()*0.7);
  std::cout<<this<<std::endl;
  imManager = imagesManager::getInstance();
 
  imageWidget = new CVImageWidget(this);
  scrollArea = new imageScrollArea(this);
  headerTable = new  imageHeader(this);
  imaStatTable = new imageStatTable(this);
  imageManagerSelector = new imageListSelector(this);
  //QTextEdit *textTest = new QTextEdit("titi", this);
  scrollArea->setMouseTracking(true);
  
  
  cursorInfoText = new coordDisplayer(this);
  //cursorInfoText->move(5,240);
  //cursorInfoText->resize(260,30);
  grille->addWidget(headerTable, 0,0,2,1);
  grille->addWidget(scrollArea,0,1,6,6);
  //grille->addWidget(cursorInfoText,1,7);
  grille->setColumnStretch(0,0);
  grille->setColumnStretch(1,0);
  grille->setColumnStretch(2,2);
  grille->setColumnStretch(7,1);
  

  customPlot = new QCustomPlot(this);
  grille->addWidget(customPlot,2,0,2,1);
  grille->addWidget(imaStatTable,4,0,2,1);
  grille->addWidget(imageManagerSelector,0,7,2,1);
  //grille->addWidget(textTest, 0,7,2,1);

  QMenuBar *mainMenu = new QMenuBar( this );
  QMenu *fileMenu = mainMenu->addMenu("File");
  QMenu *imageMenu = mainMenu->addMenu("Image");
  QMenu *colorMapMenu = mainMenu->addMenu("ColorMap");
  QMenu *helpMenu = mainMenu->addMenu("Help");
  grille->setMenuBar(mainMenu);
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

  imageFilters* ImageFilters = new imageFilters();
  imageLoader* imaLoader = new imageLoader();

  connect(scrollArea, SIGNAL(rescaleImageDynamiqSig(double, double)), imageWidget, SLOT(rescaleImageDynamiq(double, double)));
 
  connect(scrollArea, SIGNAL(displayFlyingPosInImageSig(int, int)), cursorInfoText, SLOT(displayFlyingPosInImage(int, int)));

  helpMenu->addAction(helpAct);
  fileMenu->addAction(openAct);
  connect(openAct, SIGNAL(triggered()), this, SLOT(openDialogFile()));
                                                           
  connect(this, SIGNAL(fileNameChanged(QString)), imaLoader, SLOT(readFitsImage(QString)));
  connect(imaLoader, SIGNAL(imageLoadedDone()), this, SLOT(showOrigImage()));
  connect(imaLoader, SIGNAL(imageLoadedDone()), headerTable, SLOT(updateContent()));
  connect(imaLoader, SIGNAL(imageLoadedDone()), imaStatTable, SLOT(updateContent()));

  imageMenu->addAction(backToOrigImageAct);
  connect(backToOrigImageAct,SIGNAL(triggered()), this, SLOT(showOrigImage()));
  
  imageMenu->addAction(gaussianFilterAct);
  connect(gaussianFilterAct, SIGNAL(triggered()), ImageFilters, SLOT(gaussianFilter()));
 
  imageMenu->addAction(medianFilterAct);
  connect(medianFilterAct, SIGNAL(triggered()), ImageFilters, SLOT(medianFilter()));
  
  imageMenu->addAction(sobelFilterAct);
  connect(sobelFilterAct, SIGNAL(triggered()), ImageFilters, SLOT(sobelFilter()));

  imageMenu->addAction(cannyEdgesAct);
  connect(cannyEdgesAct, SIGNAL(triggered()), ImageFilters, SLOT(cannyFilter()));
  
  imageMenu->addAction(houghCircleAct);
  connect(houghCircleAct, SIGNAL(triggered()), ImageFilters, SLOT(houghFilter()));
 
  connect(ImageFilters, SIGNAL(filterExecutionDone()), this, SLOT(showFilteredImage()));
  
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
  connect(imManager, SIGNAL(changeOnImageList()), imageManagerSelector, SLOT(buildListImageSelector()));
  
}


void fondaWin::openDialogFile()
{
  
  this->fileName  = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.fits *.fit *.fts)");
  emit fileNameChanged(this->fileName);
}

void fondaWin::showFilteredImage()
{
  imageContainer *imC = imManager->getLastContainedImageInList();
  imageWidget->setMat(*(imC->getImageMatrix()));
}

 void fondaWin::showOrigImage()
{
  imageContainer *imC = imManager->getFirstLoadedImage();
  std::cout<<"imCPointer = "<< imC<<std::endl;
 
  imageWidget->setMat(*(imC->getImageMatrix()));
  // juste en depanage  trouver une maniere propre
  scrollArea->setWidget(imageWidget->getLabel());
  // fin juste en depannage trouver
}

void fondaWin::loadImage()
{ 
    
    std::vector<float> vectImage;
    /* for (int j = 0; j<ax2; ++j)
      {
	for(int k=0; k<ax1 ; ++k)
	  {
	    matriceImage->at<float>(ax2-1-j,k) = contents[k+j*ax1];
	    vectImage.push_back(contents[k+j*ax1]);
	  }	
	
	  }
    readImage = new imageContainer(matriceImage,"loadedImages");
    readImage->setLoadedOn();
    imManager->addImageContainerInList(readImage);

    std::sort (vectImage.begin(),vectImage.end());
    // TEST POUR UN HISTOGRAMMe!!
    double maxIm = 0;
    double minIm = 0;
    cv::minMaxLoc(*matriceImage, &minIm, &maxIm, 0, 0);
   
    cv::Mat meanIm0;
    cv::Mat stdDevIm0; 
    cv::meanStdDev(*matriceImage, meanIm0, stdDevIm0);
    int histSize = maxIm;
    imageStatTable->setRowCount(5);
    imageStatTable->setColumnCount(2);
    QTableWidgetItem *maxItem = new QTableWidgetItem();
    imageStatTable->setItem(0,0,maxItem);
    maxItem->setText("max");
    QTableWidgetItem *maxItemValue = new QTableWidgetItem();
    imageStatTable->setItem(0,1,maxItemValue);
    maxItemValue->setText(QString::number(maxIm));
    
          
    QTableWidgetItem *minItem = new QTableWidgetItem();
    imageStatTable->setItem(1,0,minItem);
    minItem->setText("min");
    QTableWidgetItem *minItemValue = new QTableWidgetItem();
    imageStatTable->setItem(1,1,minItemValue);
    minItemValue->setText(QString::number(minIm));

    QTableWidgetItem *meanItem = new QTableWidgetItem();
    imageStatTable->setItem(2,0,meanItem);
    meanItem->setText("mean");
    QTableWidgetItem *meanItemValue = new QTableWidgetItem();
    imageStatTable->setItem(2,1,meanItemValue);
    meanItemValue->setText(QString::number(meanIm0.at<double>(0,0)));

    QTableWidgetItem *stdDevItem = new QTableWidgetItem();
    imageStatTable->setItem(3,0,stdDevItem);
    stdDevItem->setText("stdDev");
    QTableWidgetItem *stdDevItemValue = new QTableWidgetItem();
    imageStatTable->setItem(3,1,stdDevItemValue);
    stdDevItemValue->setText(QString::number(stdDevIm0.at<double>(0,0)));

    QTableWidgetItem *medianItem = new QTableWidgetItem();
    imageStatTable->setItem(4,0,medianItem);
    medianItem->setText("median");
    QTableWidgetItem *medianItemValue = new QTableWidgetItem();
    imageStatTable->setItem(4,1,medianItemValue);
    medianItemValue->setText(QString::number(vectImage[vectImage.size()/2]));



    

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
    customPlot->xAxis->setLabel("pixel values");
    customPlot->yAxis->setLabel("relative nb pix");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, histSize);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
      
    imageWidget->setMat(*matriceImage);
    // imageWidget->move(280,40);
    //scrollArea = new QScrollArea(this);
       //scrollArea->setBackgroundRole(QPalette::Dark);
   
    
    
   
    

    
    //get the keyword
    std::map< string, CCfits::Keyword * > & filesKeyword=image.keyWord();
     headerTable->setRowCount(filesKeyword.size());
     headerTable->setColumnCount(3);
    // headerTable = new QTableWidget(filesKeyword.size(),3,this);
  
    //show the content of the keyword map in a QtableWidget
    int cpt=0;
       }
    */
}
