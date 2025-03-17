/****************************************************************************
** Meta object code from reading C++ file 'mainwindow_red.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../OPD_PROJ_2/OPD_proj2/mainwindow_red.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow_red.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mainwindow_red_t {
    QByteArrayData data[13];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainwindow_red_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainwindow_red_t qt_meta_stringdata_mainwindow_red = {
    {
QT_MOC_LITERAL(0, 0, 14), // "mainwindow_red"
QT_MOC_LITERAL(1, 15, 8), // "add_atom"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "add_kon"
QT_MOC_LITERAL(4, 33, 7), // "add_diz"
QT_MOC_LITERAL(5, 41, 7), // "add_not"
QT_MOC_LITERAL(6, 49, 11), // "recieveData"
QT_MOC_LITERAL(7, 61, 14), // "EntityVariable"
QT_MOC_LITERAL(8, 76, 3), // "ev1"
QT_MOC_LITERAL(9, 80, 3), // "ev2"
QT_MOC_LITERAL(10, 84, 13), // "update_values"
QT_MOC_LITERAL(11, 98, 8), // "Formula*"
QT_MOC_LITERAL(12, 107, 7) // "formula"

    },
    "mainwindow_red\0add_atom\0\0add_kon\0"
    "add_diz\0add_not\0recieveData\0EntityVariable\0"
    "ev1\0ev2\0update_values\0Formula*\0formula"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainwindow_red[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    2,   48,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void mainwindow_red::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mainwindow_red *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_atom(); break;
        case 1: _t->add_kon(); break;
        case 2: _t->add_diz(); break;
        case 3: _t->add_not(); break;
        case 4: _t->recieveData((*reinterpret_cast< EntityVariable(*)>(_a[1])),(*reinterpret_cast< EntityVariable(*)>(_a[2]))); break;
        case 5: _t->update_values((*reinterpret_cast< Formula*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mainwindow_red::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_mainwindow_red.data,
    qt_meta_data_mainwindow_red,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mainwindow_red::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainwindow_red::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mainwindow_red.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int mainwindow_red::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
