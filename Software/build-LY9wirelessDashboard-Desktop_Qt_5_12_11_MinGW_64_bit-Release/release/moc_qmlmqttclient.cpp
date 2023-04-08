/****************************************************************************
** Meta object code from reading C++ file 'qmlmqttclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LY9wirelessDashboard/qmlmqttclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmlmqttclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QmlMqttSubscription_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlMqttSubscription_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QmlMqttSubscription_t qt_meta_stringdata_QmlMqttSubscription = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QmlMqttSubscription"
QT_MOC_LITERAL(1, 20, 12), // "topicChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "messageReceived"
QT_MOC_LITERAL(4, 50, 3), // "msg"
QT_MOC_LITERAL(5, 54, 5), // "topic"
QT_MOC_LITERAL(6, 60, 16) // "QMqttTopicFilter"

    },
    "QmlMqttSubscription\0topicChanged\0\0"
    "messageReceived\0msg\0topic\0QMqttTopicFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlMqttSubscription[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       3,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    4,

 // properties: name, type, flags
       5, 0x80000000 | 6, 0x0049500b,

 // properties: notify_signal_id
       0,

       0        // eod
};

void QmlMqttSubscription::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QmlMqttSubscription *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->topicChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QmlMqttSubscription::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttSubscription::topicChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QmlMqttSubscription::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttSubscription::messageReceived)) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicFilter >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QmlMqttSubscription *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QMqttTopicFilter*>(_v) = _t->m_topic; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QmlMqttSubscription *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_topic != *reinterpret_cast< QMqttTopicFilter*>(_v)) {
                _t->m_topic = *reinterpret_cast< QMqttTopicFilter*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QmlMqttSubscription::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QmlMqttSubscription.data,
    qt_meta_data_QmlMqttSubscription,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QmlMqttSubscription::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QmlMqttSubscription::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QmlMqttSubscription.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QmlMqttSubscription::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QmlMqttSubscription::topicChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QmlMqttSubscription::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_QmlMqttClient_t {
    QByteArrayData data[44];
    char stringdata0[558];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlMqttClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QmlMqttClient_t qt_meta_stringdata_QmlMqttClient = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QmlMqttClient"
QT_MOC_LITERAL(1, 14, 15), // "carSpeedChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "motorSpeedChanged"
QT_MOC_LITERAL(4, 49, 15), // "batLevelChanged"
QT_MOC_LITERAL(5, 65, 14), // "batTempChanged"
QT_MOC_LITERAL(6, 80, 14), // "throPosChanged"
QT_MOC_LITERAL(7, 95, 15), // "gearModeChanged"
QT_MOC_LITERAL(8, 111, 14), // "carModeChanged"
QT_MOC_LITERAL(9, 126, 15), // "batAlarmChanged"
QT_MOC_LITERAL(10, 142, 16), // "timeCountChanged"
QT_MOC_LITERAL(11, 159, 13), // "batVolChanged"
QT_MOC_LITERAL(12, 173, 15), // "mcu2TempChanged"
QT_MOC_LITERAL(13, 189, 15), // "mcu1TempChanged"
QT_MOC_LITERAL(14, 205, 18), // "carDistanceChanged"
QT_MOC_LITERAL(15, 224, 18), // "brakeTravelChanged"
QT_MOC_LITERAL(16, 243, 17), // "rmotorTempChanged"
QT_MOC_LITERAL(17, 261, 17), // "lmotorTempChanged"
QT_MOC_LITERAL(18, 279, 18), // "rmotorSpeedChanged"
QT_MOC_LITERAL(19, 298, 18), // "lmotorSpeedChanged"
QT_MOC_LITERAL(20, 317, 9), // "onDataRec"
QT_MOC_LITERAL(21, 327, 12), // "QMqttMessage"
QT_MOC_LITERAL(22, 340, 4), // "qmsg"
QT_MOC_LITERAL(23, 345, 9), // "subscribe"
QT_MOC_LITERAL(24, 355, 20), // "QmlMqttSubscription*"
QT_MOC_LITERAL(25, 376, 5), // "topic"
QT_MOC_LITERAL(26, 382, 8), // "carSpeed"
QT_MOC_LITERAL(27, 391, 10), // "motorSpeed"
QT_MOC_LITERAL(28, 402, 8), // "batLevel"
QT_MOC_LITERAL(29, 411, 7), // "batTemp"
QT_MOC_LITERAL(30, 419, 10), // "lmotorTemp"
QT_MOC_LITERAL(31, 430, 10), // "rmotorTemp"
QT_MOC_LITERAL(32, 441, 11), // "lmotorSpeed"
QT_MOC_LITERAL(33, 453, 11), // "rmotorSpeed"
QT_MOC_LITERAL(34, 465, 7), // "throPos"
QT_MOC_LITERAL(35, 473, 8), // "gearMode"
QT_MOC_LITERAL(36, 482, 7), // "carMode"
QT_MOC_LITERAL(37, 490, 11), // "carDistance"
QT_MOC_LITERAL(38, 502, 11), // "brakeTravel"
QT_MOC_LITERAL(39, 514, 8), // "mcu1Temp"
QT_MOC_LITERAL(40, 523, 8), // "mcu2Temp"
QT_MOC_LITERAL(41, 532, 6), // "batVol"
QT_MOC_LITERAL(42, 539, 9), // "timeCount"
QT_MOC_LITERAL(43, 549, 8) // "batAlarm"

    },
    "QmlMqttClient\0carSpeedChanged\0\0"
    "motorSpeedChanged\0batLevelChanged\0"
    "batTempChanged\0throPosChanged\0"
    "gearModeChanged\0carModeChanged\0"
    "batAlarmChanged\0timeCountChanged\0"
    "batVolChanged\0mcu2TempChanged\0"
    "mcu1TempChanged\0carDistanceChanged\0"
    "brakeTravelChanged\0rmotorTempChanged\0"
    "lmotorTempChanged\0rmotorSpeedChanged\0"
    "lmotorSpeedChanged\0onDataRec\0QMqttMessage\0"
    "qmsg\0subscribe\0QmlMqttSubscription*\0"
    "topic\0carSpeed\0motorSpeed\0batLevel\0"
    "batTemp\0lmotorTemp\0rmotorTemp\0lmotorSpeed\0"
    "rmotorSpeed\0throPos\0gearMode\0carMode\0"
    "carDistance\0brakeTravel\0mcu1Temp\0"
    "mcu2Temp\0batVol\0timeCount\0batAlarm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlMqttClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
      18,  138, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,
       4,    0,  116,    2, 0x06 /* Public */,
       5,    0,  117,    2, 0x06 /* Public */,
       6,    0,  118,    2, 0x06 /* Public */,
       7,    0,  119,    2, 0x06 /* Public */,
       8,    0,  120,    2, 0x06 /* Public */,
       9,    0,  121,    2, 0x06 /* Public */,
      10,    0,  122,    2, 0x06 /* Public */,
      11,    0,  123,    2, 0x06 /* Public */,
      12,    0,  124,    2, 0x06 /* Public */,
      13,    0,  125,    2, 0x06 /* Public */,
      14,    0,  126,    2, 0x06 /* Public */,
      15,    0,  127,    2, 0x06 /* Public */,
      16,    0,  128,    2, 0x06 /* Public */,
      17,    0,  129,    2, 0x06 /* Public */,
      18,    0,  130,    2, 0x06 /* Public */,
      19,    0,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  132,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      23,    1,  135,    2, 0x02 /* Public */,

 // signals: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21,   22,

 // methods: parameters
    0x80000000 | 24, QMetaType::QString,   25,

 // properties: name, type, flags
      26, QMetaType::UInt, 0x00495103,
      27, QMetaType::UInt, 0x00495103,
      28, QMetaType::UInt, 0x00495103,
      29, QMetaType::UInt, 0x00495103,
      30, QMetaType::UInt, 0x00495103,
      31, QMetaType::UInt, 0x00495103,
      32, QMetaType::UInt, 0x00495103,
      33, QMetaType::UInt, 0x00495103,
      34, QMetaType::UInt, 0x00495103,
      35, QMetaType::UInt, 0x00495103,
      36, QMetaType::UInt, 0x00495103,
      37, QMetaType::UInt, 0x00495103,
      38, QMetaType::UInt, 0x00495103,
      39, QMetaType::UInt, 0x00495103,
      40, QMetaType::UInt, 0x00495103,
      41, QMetaType::UInt, 0x00495103,
      42, QMetaType::Int, 0x00495103,
      43, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
      15,
      14,
      17,
      16,
       4,
       5,
       6,
      12,
      13,
      11,
      10,
       9,
       8,
       7,

       0        // eod
};

void QmlMqttClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QmlMqttClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->carSpeedChanged(); break;
        case 1: _t->motorSpeedChanged(); break;
        case 2: _t->batLevelChanged(); break;
        case 3: _t->batTempChanged(); break;
        case 4: _t->throPosChanged(); break;
        case 5: _t->gearModeChanged(); break;
        case 6: _t->carModeChanged(); break;
        case 7: _t->batAlarmChanged(); break;
        case 8: _t->timeCountChanged(); break;
        case 9: _t->batVolChanged(); break;
        case 10: _t->mcu2TempChanged(); break;
        case 11: _t->mcu1TempChanged(); break;
        case 12: _t->carDistanceChanged(); break;
        case 13: _t->brakeTravelChanged(); break;
        case 14: _t->rmotorTempChanged(); break;
        case 15: _t->lmotorTempChanged(); break;
        case 16: _t->rmotorSpeedChanged(); break;
        case 17: _t->lmotorSpeedChanged(); break;
        case 18: _t->onDataRec((*reinterpret_cast< const QMqttMessage(*)>(_a[1]))); break;
        case 19: { QmlMqttSubscription* _r = _t->subscribe((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QmlMqttSubscription**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttMessage >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::carSpeedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::motorSpeedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::batLevelChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::batTempChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::throPosChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::gearModeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::carModeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::batAlarmChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::timeCountChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::batVolChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::mcu2TempChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::mcu1TempChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::carDistanceChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::brakeTravelChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::rmotorTempChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::lmotorTempChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::rmotorSpeedChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (QmlMqttClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlMqttClient::lmotorSpeedChanged)) {
                *result = 17;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QmlMqttClient *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< uint*>(_v) = _t->carSpeed(); break;
        case 1: *reinterpret_cast< uint*>(_v) = _t->motorSpeed(); break;
        case 2: *reinterpret_cast< uint*>(_v) = _t->batLevel(); break;
        case 3: *reinterpret_cast< uint*>(_v) = _t->batTemp(); break;
        case 4: *reinterpret_cast< uint*>(_v) = _t->lmotorTemp(); break;
        case 5: *reinterpret_cast< uint*>(_v) = _t->rmotorTemp(); break;
        case 6: *reinterpret_cast< uint*>(_v) = _t->lmotorSpeed(); break;
        case 7: *reinterpret_cast< uint*>(_v) = _t->rmotorSpeed(); break;
        case 8: *reinterpret_cast< uint*>(_v) = _t->throPos(); break;
        case 9: *reinterpret_cast< uint*>(_v) = _t->gearMode(); break;
        case 10: *reinterpret_cast< uint*>(_v) = _t->carMode(); break;
        case 11: *reinterpret_cast< uint*>(_v) = _t->carDistance(); break;
        case 12: *reinterpret_cast< uint*>(_v) = _t->brakeTravel(); break;
        case 13: *reinterpret_cast< uint*>(_v) = _t->mcu1Temp(); break;
        case 14: *reinterpret_cast< uint*>(_v) = _t->mcu2Temp(); break;
        case 15: *reinterpret_cast< uint*>(_v) = _t->batVol(); break;
        case 16: *reinterpret_cast< int*>(_v) = _t->timeCount(); break;
        case 17: *reinterpret_cast< bool*>(_v) = _t->batAlarm(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QmlMqttClient *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCarSpeed(*reinterpret_cast< uint*>(_v)); break;
        case 1: _t->setMotorSpeed(*reinterpret_cast< uint*>(_v)); break;
        case 2: _t->setBatLevel(*reinterpret_cast< uint*>(_v)); break;
        case 3: _t->setBatTemp(*reinterpret_cast< uint*>(_v)); break;
        case 4: _t->setLmotorTemp(*reinterpret_cast< uint*>(_v)); break;
        case 5: _t->setRmotorTemp(*reinterpret_cast< uint*>(_v)); break;
        case 6: _t->setLmotorSpeed(*reinterpret_cast< uint*>(_v)); break;
        case 7: _t->setRmotorSpeed(*reinterpret_cast< uint*>(_v)); break;
        case 8: _t->setThroPos(*reinterpret_cast< uint*>(_v)); break;
        case 9: _t->setGearMode(*reinterpret_cast< uint*>(_v)); break;
        case 10: _t->setCarMode(*reinterpret_cast< uint*>(_v)); break;
        case 11: _t->setCarDistance(*reinterpret_cast< uint*>(_v)); break;
        case 12: _t->setBrakeTravel(*reinterpret_cast< uint*>(_v)); break;
        case 13: _t->setMcu1Temp(*reinterpret_cast< uint*>(_v)); break;
        case 14: _t->setMcu2Temp(*reinterpret_cast< uint*>(_v)); break;
        case 15: _t->setBatVol(*reinterpret_cast< uint*>(_v)); break;
        case 16: _t->setTimeCount(*reinterpret_cast< int*>(_v)); break;
        case 17: _t->setBatAlarm(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QmlMqttClient::staticMetaObject = { {
    &QMqttClient::staticMetaObject,
    qt_meta_stringdata_QmlMqttClient.data,
    qt_meta_data_QmlMqttClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QmlMqttClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QmlMqttClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QmlMqttClient.stringdata0))
        return static_cast<void*>(this);
    return QMqttClient::qt_metacast(_clname);
}

int QmlMqttClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMqttClient::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 18;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QmlMqttClient::carSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QmlMqttClient::motorSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QmlMqttClient::batLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QmlMqttClient::batTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QmlMqttClient::throPosChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QmlMqttClient::gearModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QmlMqttClient::carModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QmlMqttClient::batAlarmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QmlMqttClient::timeCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void QmlMqttClient::batVolChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void QmlMqttClient::mcu2TempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void QmlMqttClient::mcu1TempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void QmlMqttClient::carDistanceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void QmlMqttClient::brakeTravelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void QmlMqttClient::rmotorTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void QmlMqttClient::lmotorTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void QmlMqttClient::rmotorSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void QmlMqttClient::lmotorSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
