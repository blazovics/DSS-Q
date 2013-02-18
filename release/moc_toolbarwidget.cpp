/****************************************************************************
** Meta object code from reading C++ file 'toolbarwidget.h'
**
** Created: Mon Feb 18 17:24:38 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT_UI/toolbarwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolBarWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      29,   14,   14,   14, 0x0a,
      44,   14,   14,   14, 0x0a,
      58,   14,   14,   14, 0x0a,
      72,   14,   14,   14, 0x0a,
      86,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ToolBarWidget[] = {
    "ToolBarWidget\0\0playPressed()\0"
    "pausePressed()\0stepPressed()\0stopPressed()\0"
    "savePressed()\0loadPressed()\0"
};

const QMetaObject ToolBarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolBarWidget,
      qt_meta_data_ToolBarWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolBarWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBarWidget))
        return static_cast<void*>(const_cast< ToolBarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToolBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playPressed(); break;
        case 1: pausePressed(); break;
        case 2: stepPressed(); break;
        case 3: stopPressed(); break;
        case 4: savePressed(); break;
        case 5: loadPressed(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
