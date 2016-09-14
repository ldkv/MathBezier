/****************************************************************************
** Meta object code from reading C++ file 'bezierqt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/bezierqt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bezierqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BezierQt_t {
    QByteArrayData data[15];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BezierQt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BezierQt_t qt_meta_stringdata_BezierQt = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BezierQt"
QT_MOC_LITERAL(1, 9, 7), // "nouveau"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "ajouter"
QT_MOC_LITERAL(4, 26, 10), // "modeCalcul"
QT_MOC_LITERAL(5, 37, 11), // "changeColor"
QT_MOC_LITERAL(6, 49, 11), // "colorDialog"
QT_MOC_LITERAL(7, 61, 2), // "id"
QT_MOC_LITERAL(8, 64, 11), // "parametrage"
QT_MOC_LITERAL(9, 76, 14), // "transformation"
QT_MOC_LITERAL(10, 91, 10), // "changerPas"
QT_MOC_LITERAL(11, 102, 10), // "enableMenu"
QT_MOC_LITERAL(12, 113, 12), // "updateStatus"
QT_MOC_LITERAL(13, 126, 12), // "raccordement"
QT_MOC_LITERAL(14, 139, 7) // "quitter"

    },
    "BezierQt\0nouveau\0\0ajouter\0modeCalcul\0"
    "changeColor\0colorDialog\0id\0parametrage\0"
    "transformation\0changerPas\0enableMenu\0"
    "updateStatus\0raccordement\0quitter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BezierQt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BezierQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BezierQt *_t = static_cast<BezierQt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nouveau(); break;
        case 1: _t->ajouter(); break;
        case 2: _t->modeCalcul(); break;
        case 3: _t->changeColor(); break;
        case 4: _t->colorDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->parametrage(); break;
        case 6: _t->transformation(); break;
        case 7: _t->changerPas(); break;
        case 8: _t->enableMenu(); break;
        case 9: _t->updateStatus(); break;
        case 10: _t->raccordement(); break;
        case 11: _t->quitter(); break;
        default: ;
        }
    }
}

const QMetaObject BezierQt::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BezierQt.data,
      qt_meta_data_BezierQt,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BezierQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BezierQt::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BezierQt.stringdata0))
        return static_cast<void*>(const_cast< BezierQt*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BezierQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
