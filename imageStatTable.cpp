#include "imageStatTable.h"

imageStatTable::imageStatTable():QTableWidget()
{
  _imaManager = imagesManager::getInstance();
}

imageStatTable::imageStatTable(QWidget *parent) :  QTableWidget(parent)
{
  _imaManager = imagesManager::getInstance();
}						   

void imageStatTable::updateContent()
{
  // TODO ENCAPSULER DANS UN TRY
  imageContainer *curIma = _imaManager->getSelectedImage();
  
  this->setColumnCount(2);
  this->setRowCount(4);
  
  QTableWidgetItem *currentItemMean = new QTableWidgetItem();
  this->setItem(0,0, currentItemMean);
  currentItemMean->setText("Mean");
  QTableWidgetItem *currentItemMeanVal = new QTableWidgetItem();
  this->setItem(0,1,currentItemMeanVal);
  currentItemMeanVal->setText(QString::number(curIma->getMean()));
 
  QTableWidgetItem *currentItemStdDev = new QTableWidgetItem();
  this->setItem(1,0,currentItemStdDev);
  currentItemStdDev->setText("Std Dev");
  QTableWidgetItem *currentItemStdDevVal = new QTableWidgetItem();
  this->setItem(1,1,currentItemStdDevVal);
  currentItemStdDevVal->setText(QString::number(curIma->getStdDev()));

  QTableWidgetItem *currentItemMin = new QTableWidgetItem();
  this->setItem(2,0,currentItemMin);
  currentItemMin->setText("Min");
  QTableWidgetItem *currentItemMinVal = new QTableWidgetItem();
  this->setItem(2,1,currentItemMinVal);
  currentItemMinVal->setText(QString::number(curIma->getMin()));

  QTableWidgetItem *currentItemMax = new QTableWidgetItem();
  this->setItem(3,0,currentItemMax);
  currentItemMax->setText("Max");		
  QTableWidgetItem *currentItemMaxVal = new QTableWidgetItem();
  this->setItem(3,1,currentItemMaxVal);
  currentItemMaxVal->setText(QString::number(curIma->getMax()));
  
}

