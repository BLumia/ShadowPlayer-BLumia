/****************************************************************************
** Meta object code from reading C++ file 'playlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ShadowPlayer/playlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayList_t {
    QByteArrayData data[21];
    char stringdata[366];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayList_t qt_meta_stringdata_PlayList = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 10),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 34),
QT_MOC_LITERAL(4, 56, 3),
QT_MOC_LITERAL(5, 60, 23),
QT_MOC_LITERAL(6, 84, 27),
QT_MOC_LITERAL(7, 112, 11),
QT_MOC_LITERAL(8, 124, 10),
QT_MOC_LITERAL(9, 135, 14),
QT_MOC_LITERAL(10, 150, 19),
QT_MOC_LITERAL(11, 170, 12),
QT_MOC_LITERAL(12, 183, 9),
QT_MOC_LITERAL(13, 193, 14),
QT_MOC_LITERAL(14, 208, 12),
QT_MOC_LITERAL(15, 221, 14),
QT_MOC_LITERAL(16, 236, 27),
QT_MOC_LITERAL(17, 264, 36),
QT_MOC_LITERAL(18, 301, 5),
QT_MOC_LITERAL(19, 307, 29),
QT_MOC_LITERAL(20, 337, 28)
    },
    "PlayList\0callPlayer\0\0"
    "on_playListTable_cellDoubleClicked\0"
    "row\0on_searchButton_clicked\0"
    "on_searchNextButton_clicked\0setLenFiler\0"
    "showFinder\0openFileFloder\0addFromFloderToList\0"
    "insertToList\0addToList\0removeFromList\0"
    "clearCurList\0listFileCopyer\0"
    "on_listOptionButton_clicked\0"
    "on_playListCombo_currentIndexChanged\0"
    "index\0on_fliterOptionButton_clicked\0"
    "on_musicOptionButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,  100,    2, 0x08 /* Private */,
       5,    0,  105,    2, 0x08 /* Private */,
       6,    0,  106,    2, 0x08 /* Private */,
       7,    0,  107,    2, 0x08 /* Private */,
       8,    0,  108,    2, 0x08 /* Private */,
       9,    0,  109,    2, 0x08 /* Private */,
      10,    0,  110,    2, 0x08 /* Private */,
      11,    0,  111,    2, 0x08 /* Private */,
      12,    0,  112,    2, 0x08 /* Private */,
      13,    0,  113,    2, 0x08 /* Private */,
      14,    0,  114,    2, 0x08 /* Private */,
      15,    0,  115,    2, 0x08 /* Private */,
      16,    0,  116,    2, 0x08 /* Private */,
      17,    1,  117,    2, 0x08 /* Private */,
      19,    0,  120,    2, 0x08 /* Private */,
      20,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    2,
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
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayList *_t = static_cast<PlayList *>(_o);
        switch (_id) {
        case 0: _t->callPlayer(); break;
        case 1: _t->on_playListTable_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_searchButton_clicked(); break;
        case 3: _t->on_searchNextButton_clicked(); break;
        case 4: _t->setLenFiler(); break;
        case 5: _t->showFinder(); break;
        case 6: _t->openFileFloder(); break;
        case 7: _t->addFromFloderToList(); break;
        case 8: _t->insertToList(); break;
        case 9: _t->addToList(); break;
        case 10: _t->removeFromList(); break;
        case 11: _t->clearCurList(); break;
        case 12: { bool _r = _t->listFileCopyer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->on_listOptionButton_clicked(); break;
        case 14: _t->on_playListCombo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_fliterOptionButton_clicked(); break;
        case 16: _t->on_musicOptionButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayList::callPlayer)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject PlayList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayList.data,
      qt_meta_data_PlayList,  qt_static_metacall, 0, 0}
};


const QMetaObject *PlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayList.stringdata))
        return static_cast<void*>(const_cast< PlayList*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void PlayList::callPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
