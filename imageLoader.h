//imageLoader.h

#ifndef __IMAGELOADER__H__
#define __IMAGELOADER__H__
#include <QApplication>
#include <QWidget>
#include "imageContainer.h"
#include <QString>
#include <string>

//include opencv
#include <opencv2/core/core.hpp>

//include ccfits
#include <CCfits>
//mes includes
#include <cvimagewidget.h>
#include <imageScrollArea.h>
#include <qcustomplot.h>
#include <coordDisplayer.h>
#include <imageFilters.h>
#include "imagesManager.h"
#include "imageContainer.h"
#include "imageListSelector.h"
#include "imageLoader.h"
#include <QString> 

class imageLoader : public QObject
{
  Q_OBJECT
   
  public: 
   imageLoader();
   // ~imageLoader();
  
// imageLoader(std::string filename);
  
   void setFilename(QString filename);
 public slots:
   void readFitsImage(QString fname);
  
 signals:
   void imageLoadedDone();
 private:
   QString _filename;
   imageContainer * _loadedImage;
   imagesManager *_imaManager;

};

#endif //__IMAGELOADER__H__
