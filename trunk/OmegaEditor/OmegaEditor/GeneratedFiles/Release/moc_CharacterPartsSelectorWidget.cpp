/****************************************************************************
** Meta object code from reading C++ file 'CharacterPartsSelectorWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtComponents/CharacterPartsSelectorWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharacterPartsSelectorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CharacterPartsSelectorWidget_t {
    QByteArrayData data[8];
    char stringdata[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CharacterPartsSelectorWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CharacterPartsSelectorWidget_t qt_meta_stringdata_CharacterPartsSelectorWidget = {
    {
QT_MOC_LITERAL(0, 0, 28),
QT_MOC_LITERAL(1, 29, 15),
QT_MOC_LITERAL(2, 45, 0),
QT_MOC_LITERAL(3, 46, 15),
QT_MOC_LITERAL(4, 62, 19),
QT_MOC_LITERAL(5, 82, 18),
QT_MOC_LITERAL(6, 101, 19),
QT_MOC_LITERAL(7, 121, 18)
    },
    "CharacterPartsSelectorWidget\0"
    "on_head_clicked\0\0on_body_clicked\0"
    "on_rightArm_clicked\0on_leftArm_clicked\0"
    "on_rightLeg_clicked\0on_leftLeg_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CharacterPartsSelectorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08,
       3,    0,   45,    2, 0x08,
       4,    0,   46,    2, 0x08,
       5,    0,   47,    2, 0x08,
       6,    0,   48,    2, 0x08,
       7,    0,   49,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CharacterPartsSelectorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CharacterPartsSelectorWidget *_t = static_cast<CharacterPartsSelectorWidget *>(_o);
        switch (_id) {
        case 0: _t->on_head_clicked(); break;
        case 1: _t->on_body_clicked(); break;
        case 2: _t->on_rightArm_clicked(); break;
        case 3: _t->on_leftArm_clicked(); break;
        case 4: _t->on_rightLeg_clicked(); break;
        case 5: _t->on_leftLeg_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CharacterPartsSelectorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CharacterPartsSelectorWidget.data,
      qt_meta_data_CharacterPartsSelectorWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CharacterPartsSelectorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CharacterPartsSelectorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CharacterPartsSelectorWidget.stringdata))
        return static_cast<void*>(const_cast< CharacterPartsSelectorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CharacterPartsSelectorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
