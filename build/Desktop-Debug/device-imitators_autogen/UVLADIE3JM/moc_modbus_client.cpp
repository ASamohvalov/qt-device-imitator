/****************************************************************************
** Meta object code from reading C++ file 'modbus_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/modbus_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbus_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModbusClient_t {
    QByteArrayData data[7];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModbusClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModbusClient_t qt_meta_stringdata_ModbusClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ModbusClient"
QT_MOC_LITERAL(1, 13, 20), // "onModbusStateChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "QModbusDevice::State"
QT_MOC_LITERAL(4, 56, 5), // "state"
QT_MOC_LITERAL(5, 62, 11), // "onReadReady"
QT_MOC_LITERAL(6, 74, 11) // "readRequest"

    },
    "ModbusClient\0onModbusStateChanged\0\0"
    "QModbusDevice::State\0state\0onReadReady\0"
    "readRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModbusClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       5,    0,   32,    2, 0x08 /* Private */,
       6,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModbusClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModbusClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onModbusStateChanged((*reinterpret_cast< QModbusDevice::State(*)>(_a[1]))); break;
        case 1: _t->onReadReady(); break;
        case 2: _t->readRequest(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ModbusClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ModbusClient.data,
    qt_meta_data_ModbusClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ModbusClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ModbusClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
