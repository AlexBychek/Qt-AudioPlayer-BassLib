/****************************************************************************
** Meta object code from reading C++ file 'audiothread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../AudioPlayer/audiothread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audiothread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioThread_t {
    QByteArrayData data[26];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioThread_t qt_meta_stringdata_AudioThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioThread"
QT_MOC_LITERAL(1, 12, 13), // "endOfPlayback"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "curPos"
QT_MOC_LITERAL(4, 34, 8), // "Position"
QT_MOC_LITERAL(5, 43, 5), // "Total"
QT_MOC_LITERAL(6, 49, 9), // "file_data"
QT_MOC_LITERAL(7, 59, 6), // "uchar*"
QT_MOC_LITERAL(8, 66, 12), // "GetNextTrack"
QT_MOC_LITERAL(9, 79, 4), // "play"
QT_MOC_LITERAL(10, 84, 8), // "filepath"
QT_MOC_LITERAL(11, 93, 5), // "pause"
QT_MOC_LITERAL(12, 99, 6), // "resume"
QT_MOC_LITERAL(13, 106, 4), // "stop"
QT_MOC_LITERAL(14, 111, 12), // "signalUpdate"
QT_MOC_LITERAL(15, 124, 14), // "changePosition"
QT_MOC_LITERAL(16, 139, 8), // "position"
QT_MOC_LITERAL(17, 148, 9), // "SetVolume"
QT_MOC_LITERAL(18, 158, 3), // "vol"
QT_MOC_LITERAL(19, 162, 8), // "InitBass"
QT_MOC_LITERAL(20, 171, 2), // "hz"
QT_MOC_LITERAL(21, 174, 14), // "GetPosOfStream"
QT_MOC_LITERAL(22, 189, 14), // "SetPosOfScroll"
QT_MOC_LITERAL(23, 204, 3), // "pos"
QT_MOC_LITERAL(24, 208, 15), // "GetTimeOfStream"
QT_MOC_LITERAL(25, 224, 10) // "InitPlagin"

    },
    "AudioThread\0endOfPlayback\0\0curPos\0"
    "Position\0Total\0file_data\0uchar*\0"
    "GetNextTrack\0play\0filepath\0pause\0"
    "resume\0stop\0signalUpdate\0changePosition\0"
    "position\0SetVolume\0vol\0InitBass\0hz\0"
    "GetPosOfStream\0SetPosOfScroll\0pos\0"
    "GetTimeOfStream\0InitPlagin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    2,   95,    2, 0x06 /* Public */,
       6,    6,  100,    2, 0x06 /* Public */,
       8,    1,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  116,    2, 0x0a /* Public */,
      11,    0,  119,    2, 0x0a /* Public */,
      12,    0,  120,    2, 0x0a /* Public */,
      13,    0,  121,    2, 0x0a /* Public */,
      14,    0,  122,    2, 0x0a /* Public */,
      15,    1,  123,    2, 0x0a /* Public */,
      17,    1,  126,    2, 0x0a /* Public */,
      19,    1,  129,    2, 0x0a /* Public */,
      21,    0,  132,    2, 0x0a /* Public */,
      22,    1,  133,    2, 0x0a /* Public */,
      24,    0,  136,    2, 0x0a /* Public */,
      25,    0,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 7, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Bool, QMetaType::Int,   20,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Int,
    QMetaType::Void,

       0        // eod
};

void AudioThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endOfPlayback(); break;
        case 1: _t->curPos((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->file_data((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< uchar*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 3: _t->GetNextTrack((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->play((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->pause(); break;
        case 6: _t->resume(); break;
        case 7: _t->stop(); break;
        case 8: _t->signalUpdate(); break;
        case 9: _t->changePosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->SetVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { bool _r = _t->InitBass((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->GetPosOfStream();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->SetPosOfScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: { int _r = _t->GetTimeOfStream();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->InitPlagin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::endOfPlayback)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AudioThread::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::curPos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AudioThread::*)(QString , QString , QString , QString , uchar * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::file_data)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AudioThread::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::GetNextTrack)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AudioThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_AudioThread.data,
    qt_meta_data_AudioThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AudioThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int AudioThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void AudioThread::endOfPlayback()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AudioThread::curPos(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AudioThread::file_data(QString _t1, QString _t2, QString _t3, QString _t4, uchar * _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AudioThread::GetNextTrack(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
