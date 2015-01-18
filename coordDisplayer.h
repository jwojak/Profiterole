// coordDisplayer.h

#ifndef ____COORDDISPLAYER__H___
#define ____COORDDISPLAYER__H___

#include <QLabel>

class coordDisplayer : public QLabel
{
  Q_OBJECT
 
 public:
  coordDisplayer(QWidget *parent = NULL);

  public slots:
    void  displayFlyingPosInImage(const int x, const int y);
};


#endif // ____COORDDISPLAYER__H___
