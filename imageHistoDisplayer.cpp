#include "imageHistoDisplayer.h"

imageHistoDisplayer::imageHistoDisplayer():QCustomPlot()
{
  _imaManager = imagesManager::getInstance();
}

imageHistoDisplayer::imageHistoDisplayer(QWidget *parent) : QCustomPlot(parent)
{
  _imaManager = imagesManager::getInstance();
}

void imageHistoDisplayer::updateContent()
{

  // TODO ENCAPSULER DANS UN BLOC TRY
  imageContainer *curIma = _imaManager->getSelectedImage();
  QVector<double> *histogX = curIma->getHistogXbin();
  QVector<double> *histVal = curIma->getHistogYVal();

  this->addGraph();
  this->graph(0)->setData(*histogX,*histVal);
  for(int i=0; i<histVal->size();++i)
    {
      // if((*histVal)[i]) 
      //	std::cout<< "testValeur "<< (*histogX)[i] << std::endl; 
    }
  this->xAxis->setRange(curIma->getMin(),curIma->getMax());
  this->yAxis->setRange(0,curIma->getHistogBinMax());
  this->xAxis->setLabel("pixel values");
  this->yAxis->setLabel("nb pix");
  this->replot();
} 
