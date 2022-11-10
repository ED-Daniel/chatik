/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ChatiKClient/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[38];
    char stringdata0[11];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[14];
    char stringdata5[8];
    char stringdata6[12];
    char stringdata7[11];
    char stringdata8[5];
    char stringdata9[27];
    char stringdata10[30];
    char stringdata11[24];
    char stringdata12[26];
    char stringdata13[28];
    char stringdata14[32];
    char stringdata15[24];
    char stringdata16[26];
    char stringdata17[24];
    char stringdata18[34];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 24),  // "on_connectButton_clicked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 21),  // "on_sendButton_clicked"
        QT_MOC_LITERAL(59, 13),  // "createMessage"
        QT_MOC_LITERAL(73, 7),  // "message"
        QT_MOC_LITERAL(81, 11),  // "TextMessage"
        QT_MOC_LITERAL(93, 10),  // "setClients"
        QT_MOC_LITERAL(104, 4),  // "info"
        QT_MOC_LITERAL(109, 26),  // "on_actionConnect_triggered"
        QT_MOC_LITERAL(136, 29),  // "on_actionDisconnect_triggered"
        QT_MOC_LITERAL(166, 23),  // "on_actionExit_triggered"
        QT_MOC_LITERAL(190, 25),  // "on_actionServer_triggered"
        QT_MOC_LITERAL(216, 27),  // "on_actionUsername_triggered"
        QT_MOC_LITERAL(244, 31),  // "on_actionSave_History_triggered"
        QT_MOC_LITERAL(276, 23),  // "on_actionShow_triggered"
        QT_MOC_LITERAL(300, 25),  // "on_actionOnline_triggered"
        QT_MOC_LITERAL(326, 23),  // "on_actionAway_triggered"
        QT_MOC_LITERAL(350, 33)   // "on_actionDo_Not_Disturb_trigg..."
    },
    "MainWindow",
    "on_connectButton_clicked",
    "",
    "on_sendButton_clicked",
    "createMessage",
    "message",
    "TextMessage",
    "setClients",
    "info",
    "on_actionConnect_triggered",
    "on_actionDisconnect_triggered",
    "on_actionExit_triggered",
    "on_actionServer_triggered",
    "on_actionUsername_triggered",
    "on_actionSave_History_triggered",
    "on_actionShow_triggered",
    "on_actionOnline_triggered",
    "on_actionAway_triggered",
    "on_actionDo_Not_Disturb_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    1,  106,    2, 0x08,    3 /* Private */,
       4,    1,  109,    2, 0x08,    5 /* Private */,
       7,    1,  112,    2, 0x08,    7 /* Private */,
       9,    0,  115,    2, 0x08,    9 /* Private */,
      10,    0,  116,    2, 0x08,   10 /* Private */,
      11,    0,  117,    2, 0x08,   11 /* Private */,
      12,    0,  118,    2, 0x08,   12 /* Private */,
      13,    0,  119,    2, 0x08,   13 /* Private */,
      14,    0,  120,    2, 0x08,   14 /* Private */,
      15,    0,  121,    2, 0x08,   15 /* Private */,
      16,    0,  122,    2, 0x08,   16 /* Private */,
      17,    0,  123,    2, 0x08,   17 /* Private */,
      18,    0,  124,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 6,    5,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_connectButton_clicked(); break;
        case 1: _t->on_sendButton_clicked(); break;
        case 2: _t->createMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->createMessage((*reinterpret_cast< std::add_pointer_t<TextMessage>>(_a[1]))); break;
        case 4: _t->setClients((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 5: _t->on_actionConnect_triggered(); break;
        case 6: _t->on_actionDisconnect_triggered(); break;
        case 7: _t->on_actionExit_triggered(); break;
        case 8: _t->on_actionServer_triggered(); break;
        case 9: _t->on_actionUsername_triggered(); break;
        case 10: _t->on_actionSave_History_triggered(); break;
        case 11: _t->on_actionShow_triggered(); break;
        case 12: _t->on_actionOnline_triggered(); break;
        case 13: _t->on_actionAway_triggered(); break;
        case 14: _t->on_actionDo_Not_Disturb_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const TextMessage &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QJsonArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
