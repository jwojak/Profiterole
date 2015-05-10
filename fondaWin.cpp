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
  
  //elts on the main panel:
  imageWidget = new CVImageWidget(this);
  scrollArea = new imageScrollArea(this);
  headerTable = new  imageHeader(this);
  imaStatTable = new imageStatTable(this);
  imageManagerSelector = new imageListSelector(this);
  imaHistoDisplayer = new imageHistoDisplayer(this);
  cursorInfoText = new coordDisplayer(this);

  //QTextEdit *textTest = new QTextEdit("titi", this);
  scrollArea->setMouseTracking(true);
  
  
  
  //cursorInfoText->move(5,240);
  //cursorInfoText->resize(260,30);
  grille->addWidget(headerTable, 0,0,2,1);
  grille->addWidget(scrollArea,0,1,6,6);
  //grille->addWidget(cursorInfoText,1,7);
  grille->setColumnStretch(0,0);
  grille->setColumnStretch(1,0);
  grille->setColumnStretch(2,2);
  grille->setColumnStretch(7,1);
  

  
  grille->addWidget(imaHistoDisplayer,2,0,2,1);
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
  connect(imaLoader, SIGNAL(imageLoadedDone()), imaHistoDisplayer, SLOT(updateContent()));

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
 
  connect(ImageFilters, SIGNAL(filterExecutionDone()), this, SLOT(showSelectedImage()));
  //connect(ImageFilters, SIGNAL(filterExecutionDone()), headerTable, SLOT(updateContent()));
  connect(ImageFilters, SIGNAL(filterExecutionDone()), imaStatTable, SLOT(updateContent()));
  //connect(ImageFilters, SIGNAL(filterExecutionDone()), imaHistoDisplayer, SLOT(updateContent()));

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
  //  connect(imManager, SIGNAL(changeOnImageList()), imageManagerSelector, SLOT(buildListImageSelector()));
  
}


void fondaWin::openDialogFile()
{
  
  this->fileName  = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.fits *.fit *.fts)");
  emit fileNameChanged(this->fileName);
}

void fondaWin::showSelectedImage()
{
  imageContainer *imC = imManager->getSelectedImage();
  imageWidget->setMat(*(imC->getImageMatrix()));
}

void fondaWin::showFilteredImage()
{
  imageContainer *imC = imManager->getLastContainedImageInList();
  imageWidget->setMat(*(imC->getImageMatrix()));
}

 void fondaWin::showOrigImage()
{
  imageContainer *imC = imManager->getFirstLoadedImage();
 
  imageWidget->setMat(*(imC->getImageMatrix()));
  // juste en depanage  trouver une maniere propre
  scrollArea->setWidget(imageWidget->getLabel());
  // fin juste en depannage trouver
}

