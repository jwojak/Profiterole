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
//#include <QScrollArea>
#include <QTableWidget>
#include <QSignalMapper>

//include opencv
#include <opencv2/core/core.hpp>

//include ccfits
#include <CCfits>

//mes includes
#include <cvimagewidget.h>
#include <imageScrollArea.h>
//#include <type_traits>  // pour le prochain upgrade en c++11

enum  colorTableLUT {linear_gray, cubehelix}; // on ne met que un enum ... a upgrader en C++11 pour les prochaines versions

class fondaWin : public QWidget
{
  Q_OBJECT
  
 public:
  fondaWin();
  
  public slots:
    void openDialogFile();
    void loadImage();
    void showFilteredImage();
    void showOrigImage();
    void medianFilter();
    void cannyFilter();
    void sobelFilter();
    void gaussianFilter();
    void houghFilter();
    

 signals:
    void fileNameChanged();
    void toggleToFilteredImage();
    
 private:
    cv::Mat *matriceImage;
    cv::Mat *matriceImageFiltered;
    QString fileName;
    CVImageWidget* imageWidget;
    QScrollArea* scrollArea;
    QTableWidget *headerTable;
  
};




#endif

