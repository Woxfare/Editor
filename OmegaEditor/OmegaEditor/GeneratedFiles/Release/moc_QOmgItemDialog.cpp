/****************************************************************************
** Meta object code from reading C++ file 'QOmgItemDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtComponents/QOmgItemDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOmgItemDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QOmgItemDialog_t {
    QByteArrayData data[10];
    char stringdata[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QOmgItemDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QOmgItemDialog_t qt_meta_stringdata_QOmgItemDialog = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 33),
QT_MOC_LITERAL(2, 49, 0),
QT_MOC_LITERAL(3, 50, 4),
QT_MOC_LITERAL(4, 55, 19),
QT_MOC_LITERAL(5, 75, 20),
QT_MOC_LITERAL(6, 96, 18),
QT_MOC_LITERAL(7, 115, 23),
QT_MOC_LITERAL(8, 139, 25),
QT_MOC_LITERAL(9, 165, 24)
    },
    "QOmgItemDialog\0on_cbItemType_currentIndexChanged\0"
    "\0arg1\0on__newItem_clicked\0"
    "on__editItem_clicked\0on__cancel_clicked\0"
    "on__pb_textures_clicked\0"
    "on_deleteTextures_clicked\0"
    "on_texturesEqual_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOmgItemDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08,
       4,    0,   52,    2, 0x08,
       5,    0,   53,    2, 0x08,
       6,    0,   54,    2, 0x08,
       7,    0,   55,    2, 0x08,
       8,    0,   56,    2, 0x08,
       9,    0,   57,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QOmgItemDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QOmgItemDialog *_t = static_cast<QOmgItemDialog *>(_o);
        switch (_id) {
        case 0: _t->on_cbItemType_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on__newItem_clicked(); break;
        case 2: _t->on__editItem_clicked(); break;
        case 3: _t->on__cancel_clicked(); break;
        case 4: _t->on__pb_textures_clicked(); break;
        case 5: _t->on_deleteTextures_clicked(); break;
        case 6: _t->on_texturesEqual_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject QOmgItemDialog::staticMetaObject = {
    { &InputData::staticMetaObject, qt_meta_stringdata_QOmgItemDialog.data,
      qt_meta_data_QOmgItemDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *QOmgItemDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOmgItemDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QOmgItemDialog.stringdata))
        return static_cast<void*>(const_cast< QOmgItemDialog*>(this));
    return InputData::qt_metacast(_clname);
}

int QOmgItemDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InputData::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
