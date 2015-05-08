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
#include <QTableWidget> // TO REMOVE
#include <QSignalMapper>
#include <QGridLayout>



//include ccfits
#include <CCfits>

//mes includes
#include <cvimagewidget.h>
#include <imageScrollArea.h>
#include <coordDisplayer.h>
#include <imageFilters.h>
#include "imagesManager.h"
#include "imageContainer.h"
#include "imageListSelector.h"
#include "imageLoader.h"
#include "imageHeader.h"
#include "imageStatTable.h"
#include "imageHistoDisplayer.h"

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
    void showFilteredImage();
    void showOrigImage();   

 signals:
    void fileNameChanged(QString);
    void toggleToFilteredImage();
    
 private:
    imagesManager *imManager;
    QString fileName;
    CVImageWidget* imageWidget;
    QScrollArea* scrollArea;
    imageHeader *headerTable;
    coordDisplayer *cursorInfoText;
    imageListSelector *imageManagerSelector;
    imageStatTable *imaStatTable;
    imageHistoDisplayer *imaHistoDisplayer;
};




#endif

