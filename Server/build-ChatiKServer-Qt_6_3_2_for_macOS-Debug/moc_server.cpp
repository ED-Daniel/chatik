/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ChatiKServer/server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Server_t {
    uint offsetsAndSizes[24];
    char stringdata0[7];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[16];
    char stringdata5[11];
    char stringdata6[19];
    char stringdata7[19];
    char stringdata8[8];
    char stringdata9[17];
    char stringdata10[14];
    char stringdata11[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Server_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_Server_t qt_meta_stringdata_Server = {
    {
        QT_MOC_LITERAL(0, 6),  // "Server"
        QT_MOC_LITERAL(7, 14),  // "clientsUpdated"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 4),  // "info"
        QT_MOC_LITERAL(28, 15),  // "clientConnected"
        QT_MOC_LITERAL(44, 10),  // "ClientInfo"
        QT_MOC_LITERAL(55, 18),  // "clientDisconnected"
        QT_MOC_LITERAL(74, 18),  // "incomingConnection"
        QT_MOC_LITERAL(93, 7),  // "qintptr"
        QT_MOC_LITERAL(101, 16),  // "socketDescriptor"
        QT_MOC_LITERAL(118, 13),  // "slotReadyRead"
        QT_MOC_LITERAL(132, 16)   // "handleDisconnect"
    },
    "Server",
    "clientsUpdated",
    "",
    "info",
    "clientConnected",
    "ClientInfo",
    "clientDisconnected",
    "incomingConnection",
    "qintptr",
    "socketDescriptor",
    "slotReadyRead",
    "handleDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    1,   53,    2, 0x06,    3 /* Public */,
       6,    1,   56,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   59,    2, 0x0a,    7 /* Public */,
      10,    0,   62,    2, 0x0a,    9 /* Public */,
      11,    0,   63,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void, 0x80000000 | 5,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Server *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clientsUpdated((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 1: _t->clientConnected((*reinterpret_cast< std::add_pointer_t<ClientInfo>>(_a[1]))); break;
        case 2: _t->clientDisconnected((*reinterpret_cast< std::add_pointer_t<ClientInfo>>(_a[1]))); break;
        case 3: _t->incomingConnection((*reinterpret_cast< std::add_pointer_t<qintptr>>(_a[1]))); break;
        case 4: _t->slotReadyRead(); break;
        case 5: _t->handleDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Server::*)(const QJsonArray & );
            if (_t _q_method = &Server::clientsUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Server::*)(const ClientInfo & );
            if (_t _q_method = &Server::clientConnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Server::*)(const ClientInfo & );
            if (_t _q_method = &Server::clientDisconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Server::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpServer::staticMetaObject>(),
    qt_meta_stringdata_Server.offsetsAndSizes,
    qt_meta_data_Server,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Server_t
, QtPrivate::TypeAndForceComplete<Server, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QJsonArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const ClientInfo &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const ClientInfo &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qintptr, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Server.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Server::clientsUpdated(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Server::clientConnected(const ClientInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Server::clientDisconnected(const ClientInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
