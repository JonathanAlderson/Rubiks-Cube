/****************************************************************************
** Meta object code from reading C++ file 'RubiksWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RubiksWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RubiksWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RubiksWidget_t {
    QByteArrayData data[19];
    char stringdata[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RubiksWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RubiksWidget_t qt_meta_stringdata_RubiksWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 11),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 20),
QT_MOC_LITERAL(4, 47, 17),
QT_MOC_LITERAL(5, 65, 17),
QT_MOC_LITERAL(6, 83, 19),
QT_MOC_LITERAL(7, 103, 19),
QT_MOC_LITERAL(8, 123, 1),
QT_MOC_LITERAL(9, 125, 12),
QT_MOC_LITERAL(10, 138, 14),
QT_MOC_LITERAL(11, 153, 6),
QT_MOC_LITERAL(12, 160, 13),
QT_MOC_LITERAL(13, 174, 5),
QT_MOC_LITERAL(14, 180, 23),
QT_MOC_LITERAL(15, 204, 17),
QT_MOC_LITERAL(16, 222, 20),
QT_MOC_LITERAL(17, 243, 15),
QT_MOC_LITERAL(18, 259, 18)
    },
    "RubiksWidget\0updateScene\0\0"
    "updateCameraDistance\0updateRotateSpeed\0"
    "updateCubeSpacing\0updateEdgeThickness\0"
    "updateStretchFactor\0i\0updateRadius\0"
    "toggleConfetti\0toggle\0updateTexture\0"
    "index\0toggleRotateAboutCircle\0"
    "toggleHelperCubes\0toggleShinyMaterials\0"
    "solveCubeButton\0scrambleCubeButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RubiksWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    1,   85,    2, 0x0a /* Public */,
       4,    1,   88,    2, 0x0a /* Public */,
       5,    1,   91,    2, 0x0a /* Public */,
       6,    1,   94,    2, 0x0a /* Public */,
       7,    1,   97,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      10,    1,  103,    2, 0x0a /* Public */,
      12,    1,  106,    2, 0x0a /* Public */,
      14,    1,  109,    2, 0x0a /* Public */,
      15,    1,  112,    2, 0x0a /* Public */,
      16,    1,  115,    2, 0x0a /* Public */,
      17,    0,  118,    2, 0x0a /* Public */,
      18,    0,  119,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RubiksWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RubiksWidget *_t = static_cast<RubiksWidget *>(_o);
        switch (_id) {
        case 0: _t->updateScene(); break;
        case 1: _t->updateCameraDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateRotateSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateCubeSpacing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateEdgeThickness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateStretchFactor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->toggleConfetti((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->updateTexture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->toggleRotateAboutCircle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->toggleHelperCubes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->toggleShinyMaterials((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->solveCubeButton(); break;
        case 13: _t->scrambleCubeButton(); break;
        default: ;
        }
    }
}

const QMetaObject RubiksWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_RubiksWidget.data,
      qt_meta_data_RubiksWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *RubiksWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RubiksWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RubiksWidget.stringdata))
        return static_cast<void*>(const_cast< RubiksWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int RubiksWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
