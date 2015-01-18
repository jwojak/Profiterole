//fondaWin.h
 
#ifndef ____FONDAWIN__H____
#define ____FONDAWIN__H____

// includes qt
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
//#include <QScrollArea>
#include <QTableWidget>
#include <QSignalMapper>
 #include <QGridLayout>

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


//#include <type_traits>  // pour le prochain upgrade en c++11

enum  colorTableLUT {linear_gray, cubehelix}; // on ne met que un enum ... a upgrader en C++11 pour les prochaines versions

class fondaWin : public QWidget
{
  Q_OBJECT
  
 public:
  fondaWin();
  void setMatriceImageFiltered(cv::Mat &m);

  public slots:
    void openDialogFile();
    void loadImage();
    void showFilteredImage();
    void showOrigImage();   

 signals:
    void fileNameChanged();
    void toggleToFilteredImage();
    
 private:
    imagesManager *imManager;
    QString fileName;
    CVImageWidget* imageWidget;
    QScrollArea* scrollArea;
    QTableWidget *headerTable;
    QCustomPlot *customPlot;
    QTableWidget *imageStatTable;
    coordDisplayer *cursorInfoText;
    imageListSelector *imageManagerSelector;
};




#endif

