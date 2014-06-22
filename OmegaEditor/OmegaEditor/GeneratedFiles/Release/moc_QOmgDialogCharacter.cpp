/****************************************************************************
** Meta object code from reading C++ file 'QOmgDialogCharacter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtComponents/QOmgDialogCharacter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOmgDialogCharacter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QOmgDialogCharacter_t {
    QByteArrayData data[11];
    char stringdata[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QOmgDialogCharacter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QOmgDialogCharacter_t qt_meta_stringdata_QOmgDialogCharacter = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 22),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 21),
QT_MOC_LITERAL(4, 66, 20),
QT_MOC_LITERAL(5, 87, 21),
QT_MOC_LITERAL(6, 109, 21),
QT_MOC_LITERAL(7, 131, 23),
QT_MOC_LITERAL(8, 155, 34),
QT_MOC_LITERAL(9, 190, 4),
QT_MOC_LITERAL(10, 195, 25)
    },
    "QOmgDialogCharacter\0ChangeWidgetsForPlayer\0"
    "\0ChangeWidgetsForEnemy\0on__new_char_clicked\0"
    "on__edit_char_clicked\0on_pushButton_clicked\0"
    "on__pb_textures_clicked\0"
    "on__type_enemy_currentIndexChanged\0"
    "arg1\0on_deleteTextures_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOmgDialogCharacter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    0,   55,    2, 0x0a,
       4,    0,   56,    2, 0x0a,
       5,    0,   57,    2, 0x0a,
       6,    0,   58,    2, 0x08,
       7,    0,   59,    2, 0x08,
       8,    1,   60,    2, 0x08,
      10,    0,   63,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

void QOmgDialogCharacter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QOmgDialogCharacter *_t = static_cast<QOmgDialogCharacter *>(_o);
        switch (_id) {
        case 0: _t->ChangeWidgetsForPlayer(); break;
        case 1: _t->ChangeWidgetsForEnemy(); break;
        case 2: _t->on__new_char_clicked(); break;
        case 3: _t->on__edit_char_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on__pb_textures_clicked(); break;
        case 6: _t->on__type_enemy_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_deleteTextures_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject QOmgDialogCharacter::staticMetaObject = {
    { &InputData::staticMetaObject, qt_meta_stringdata_QOmgDialogCharacter.data,
      qt_meta_data_QOmgDialogCharacter,  qt_static_metacall, 0, 0}
};


const QMetaObject *QOmgDialogCharacter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOmgDialogCharacter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QOmgDialogCharacter.stringdata))
        return static_cast<void*>(const_cast< QOmgDialogCharacter*>(this));
    return InputData::qt_metacast(_clname);
}

int QOmgDialogCharacter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InputData::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
