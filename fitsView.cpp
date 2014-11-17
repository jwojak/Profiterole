// include opengl
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>

#include <QString>



//mes include
#include <string.h>
#include "fondaWin.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    fondaWin mainWindow;
    mainWindow.setWindowIcon(QIcon("image.png"));
    mainWindow.show();
    return app.exec();
}

