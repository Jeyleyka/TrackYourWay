/****************************************************************************
** Meta object code from reading C++ file 'modalwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../modalwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modalwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModalWindow_t {
    QByteArrayData data[10];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModalWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModalWindow_t qt_meta_stringdata_ModalWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ModalWindow"
QT_MOC_LITERAL(1, 12, 12), // "showCalendar"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "showHistory"
QT_MOC_LITERAL(4, 38, 9), // "showLogin"
QT_MOC_LITERAL(5, 48, 10), // "changeIcon"
QT_MOC_LITERAL(6, 59, 21), // "onShowCalendarClicked"
QT_MOC_LITERAL(7, 81, 20), // "onShowHistoryClicked"
QT_MOC_LITERAL(8, 102, 24), // "onLogOutOfProfileClicked"
QT_MOC_LITERAL(9, 127, 12) // "onChangeIcon"

    },
    "ModalWindow\0showCalendar\0\0showHistory\0"
    "showLogin\0changeIcon\0onShowCalendarClicked\0"
    "onShowHistoryClicked\0onLogOutOfProfileClicked\0"
    "onChangeIcon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModalWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModalWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModalWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showCalendar(); break;
        case 1: _t->showHistory(); break;
        case 2: _t->showLogin(); break;
        case 3: _t->changeIcon(); break;
        case 4: _t->onShowCalendarClicked(); break;
        case 5: _t->onShowHistoryClicked(); break;
        case 6: _t->onLogOutOfProfileClicked(); break;
        case 7: _t->onChangeIcon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModalWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModalWindow::showCalendar)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModalWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModalWindow::showHistory)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ModalWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModalWindow::showLogin)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ModalWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModalWindow::changeIcon)) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ModalWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ModalWindow.data,
    qt_meta_data_ModalWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ModalWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModalWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModalWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ModalWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ModalWindow::showCalendar()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ModalWindow::showHistory()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ModalWindow::showLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ModalWindow::changeIcon()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
