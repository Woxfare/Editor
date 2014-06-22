/****************************************************************************
** Meta object code from reading C++ file 'QOmgDragableEntities.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtComponents/QOmgDragableEntities.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOmgDragableEntities.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QOmgDragableEntities_t {
    QByteArrayData data[10];
    char stringdata[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QOmgDragableEntities_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QOmgDragableEntities_t qt_meta_stringdata_QOmgDragableEntities = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 22),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 4),
QT_MOC_LITERAL(4, 50, 18),
QT_MOC_LITERAL(5, 69, 12),
QT_MOC_LITERAL(6, 82, 13),
QT_MOC_LITERAL(7, 96, 4),
QT_MOC_LITERAL(8, 101, 22),
QT_MOC_LITERAL(9, 124, 23)
    },
    "QOmgDragableEntities\0on__search_textChanged\0"
    "\0arg1\0on__update_clicked\0ItemSelected\0"
    "QOmgListItem*\0item\0enemyDoorButtonPressed\0"
    "playerDoorButtonPressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOmgDragableEntities[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08,
       4,    0,   42,    2, 0x08,
       5,    1,   43,    2, 0x08,
       8,    0,   46,    2, 0x08,
       9,    0,   47,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QOmgDragableEntities::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QOmgDragableEntities *_t = static_cast<QOmgDragableEntities *>(_o);
        switch (_id) {
        case 0: _t->on__search_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on__update_clicked(); break;
        case 2: _t->ItemSelected((*reinterpret_cast< QOmgListItem*(*)>(_a[1]))); break;
        case 3: _t->enemyDoorButtonPressed(); break;
        case 4: _t->playerDoorButtonPressed(); break;
        default: ;
        }
    }
}

const QMetaObject QOmgDragableEntities::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QOmgDragableEntities.data,
      qt_meta_data_QOmgDragableEntities,  qt_static_metacall, 0, 0}
};


const QMetaObject *QOmgDragableEntities::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOmgDragableEntities::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QOmgDragableEntities.stringdata))
        return static_cast<void*>(const_cast< QOmgDragableEntities*>(this));
    return QWidget::qt_metacast(_clname);
}

int QOmgDragableEntities::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
