######################################################################
# Automatically generated by qmake (2.01a) mer. juil. 2 22:44:33 2014
######################################################################

TEMPLATE = app
TARGET = Profiterole
DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += /usr/local/include/CCfits
INCLUDEPATH += /home/julien/MESLIBS/cfitsio/include
 
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv

INCLUDEPATH += `pkg-config --cflags opencv`
LIBS += `pkg-config --libs opencv`
LIBS += -lCCfits

QMAKE_LIBDIR += /usr/local/lib64/CCfits
QMAKE_LIBDIR += /home/julien/MESLIBS/cfitsio/lib64

CONFIG += debug_and_release

# Input
HEADERS += cvimagewidget.h
HEADERS += imageScrollArea.h
HEADERS += qcustomplot.h
HEADERS += coordDisplayer.h
HEADERS += imageFilters.h
HEADERS += imageContainer.h
HEADERS += imagesManager.h
HEADERS += fondaWin.h
HEADERS += imageListSelector.h
SOURCES += fitsView.cpp
SOURCES += cvimagewidget.cpp
SOURCES += imageScrollArea.cpp
SOURCES += qcustomplot.cpp
SOURCES += coordDisplayer.cpp
SOURCES += imageFilters.cpp
SOURCES += imageContainer.cpp
SOURCES += imagesManager.cpp
SOURCES += fondaWin.cpp
SOURCES += imageListSelector.cpp
