/****************************************************************************
** Meta object code from reading C++ file 'fondaWin.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fondaWin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fondaWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_fondaWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      28,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,    9,    9,    9, 0x0a,
      69,    9,    9,    9, 0x0a,
      81,    9,    9,    9, 0x0a,
     101,    9,    9,    9, 0x0a,
     117,    9,    9,    9, 0x0a,
     132,    9,    9,    9, 0x0a,
     146,    9,    9,    9, 0x0a,
     160,    9,    9,    9, 0x0a,
     177,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_fondaWin[] = {
    "fondaWin\0\0fileNameChanged()\0"
    "toggleToFilteredImage()\0openDialogFile()\0"
    "loadImage()\0showFilteredImage()\0"
    "showOrigImage()\0medianFilter()\0"
    "cannyFilter()\0sobelFilter()\0"
    "gaussianFilter()\0houghFilter()\0"
};

void fondaWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fondaWin *_t = static_cast<fondaWin *>(_o);
        switch (_id) {
        case 0: _t->fileNameChanged(); break;
        case 1: _t->toggleToFilteredImage(); break;
        case 2: _t->openDialogFile(); break;
        case 3: _t->loadImage(); break;
        case 4: _t->showFilteredImage(); break;
        case 5: _t->showOrigImage(); break;
        case 6: _t->medianFilter(); break;
        case 7: _t->cannyFilter(); break;
        case 8: _t->sobelFilter(); break;
        case 9: _t->gaussianFilter(); break;
        case 10: _t->houghFilter(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData fondaWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fondaWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fondaWin,
      qt_meta_data_fondaWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fondaWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fondaWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fondaWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fondaWin))
        return static_cast<void*>(const_cast< fondaWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int fondaWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void fondaWin::fileNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void fondaWin::toggleToFilteredImage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
