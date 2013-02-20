/****************************************************************************
** Meta object code from reading C++ file 'screenwidget.h'
**
** Created: Wed Feb 20 15:58:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QT_UI/screenwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      30,   13,   13,   13, 0x0a,
      44,   13,   13,   13, 0x0a,
      59,   13,   13,   13, 0x0a,
      73,   13,   13,   13, 0x0a,
      88,   13,   13,   13, 0x0a,
     102,   13,   13,   13, 0x0a,
     116,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScreenWidget[] = {
    "ScreenWidget\0\0updateCaption()\0"
    "playPressed()\0pausePressed()\0stepPressed()\0"
    "startPressed()\0stopPressed()\0savePressed()\0"
    "loadPressed()\0"
};

void ScreenWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScreenWidget *_t = static_cast<ScreenWidget *>(_o);
        switch (_id) {
        case 0: _t->updateCaption(); break;
        case 1: _t->playPressed(); break;
        case 2: _t->pausePressed(); break;
        case 3: _t->stepPressed(); break;
        case 4: _t->startPressed(); break;
        case 5: _t->stopPressed(); break;
        case 6: _t->savePressed(); break;
        case 7: _t->loadPressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ScreenWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScreenWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScreenWidget,
      qt_meta_data_ScreenWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScreenWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScreenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScreenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenWidget))
        return static_cast<void*>(const_cast< ScreenWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScreenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
