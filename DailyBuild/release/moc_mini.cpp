/****************************************************************************
** Meta object code from reading C++ file 'mini.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ShadowPlayer/mini.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mini.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_miniForm_t {
    QByteArrayData data[19];
    char stringdata[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_miniForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_miniForm_t qt_meta_stringdata_miniForm = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 18),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 22),
QT_MOC_LITERAL(4, 52, 22),
QT_MOC_LITERAL(5, 75, 22),
QT_MOC_LITERAL(6, 98, 18),
QT_MOC_LITERAL(7, 117, 14),
QT_MOC_LITERAL(8, 132, 33),
QT_MOC_LITERAL(9, 166, 6),
QT_MOC_LITERAL(10, 173, 12),
QT_MOC_LITERAL(11, 186, 5),
QT_MOC_LITERAL(12, 192, 12),
QT_MOC_LITERAL(13, 205, 8),
QT_MOC_LITERAL(14, 214, 24),
QT_MOC_LITERAL(15, 239, 10),
QT_MOC_LITERAL(16, 250, 14),
QT_MOC_LITERAL(17, 265, 8),
QT_MOC_LITERAL(18, 274, 19)
    },
    "miniForm\0on_playBtn_clicked\0\0"
    "on_playNextBtn_clicked\0on_playPrevBtn_clicked\0"
    "on_playModeBtn_clicked\0on_muteBtn_clicked\0"
    "showMainPlayer\0QSystemTrayIcon::ActivationReason\0"
    "reason\0nowPlayValue\0value\0refreshTitle\0"
    "curTitle\0on_mainPlayerBtn_clicked\0"
    "hideMiniUi\0setSliderValue\0intvalue\0"
    "setSliderValueClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_miniForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,
      10,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   85,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    1,   90,    2, 0x08 /* Private */,
      18,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void miniForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        miniForm *_t = static_cast<miniForm *>(_o);
        switch (_id) {
        case 0: _t->on_playBtn_clicked(); break;
        case 1: _t->on_playNextBtn_clicked(); break;
        case 2: _t->on_playPrevBtn_clicked(); break;
        case 3: _t->on_playModeBtn_clicked(); break;
        case 4: _t->on_muteBtn_clicked(); break;
        case 5: _t->showMainPlayer((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 6: _t->nowPlayValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->refreshTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_mainPlayerBtn_clicked(); break;
        case 9: _t->hideMiniUi(); break;
        case 10: _t->setSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setSliderValueClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (miniForm::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::on_playBtn_clicked)) {
                *result = 0;
            }
        }
        {
            typedef void (miniForm::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::on_playNextBtn_clicked)) {
                *result = 1;
            }
        }
        {
            typedef void (miniForm::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::on_playPrevBtn_clicked)) {
                *result = 2;
            }
        }
        {
            typedef void (miniForm::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::on_playModeBtn_clicked)) {
                *result = 3;
            }
        }
        {
            typedef void (miniForm::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::on_muteBtn_clicked)) {
                *result = 4;
            }
        }
        {
            typedef void (miniForm::*_t)(QSystemTrayIcon::ActivationReason );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::showMainPlayer)) {
                *result = 5;
            }
        }
        {
            typedef void (miniForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&miniForm::nowPlayValue)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject miniForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_miniForm.data,
      qt_meta_data_miniForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *miniForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *miniForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_miniForm.stringdata))
        return static_cast<void*>(const_cast< miniForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int miniForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void miniForm::on_playBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void miniForm::on_playNextBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void miniForm::on_playPrevBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void miniForm::on_playModeBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void miniForm::on_muteBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void miniForm::showMainPlayer(QSystemTrayIcon::ActivationReason _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void miniForm::nowPlayValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
