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
    QByteArrayData data[8];
    char stringdata0[116];
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
QT_MOC_LITERAL(5, 48, 21), // "onShowCalendarClicked"
QT_MOC_LITERAL(6, 70, 20), // "onShowHistoryClicked"
QT_MOC_LITERAL(7, 91, 24) // "onLogOutOfProfileClicked"

    },
    "ModalWindow\0showCalendar\0\0showHistory\0"
    "showLogin\0onShowCalendarClicked\0"
    "onShowHistoryClicked\0onLogOutOfProfileClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModalWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
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
        case 3: _t->onShowCalendarClicked(); break;
        case 4: _t->onShowHistoryClicked(); break;
        case 5: _t->onLogOutOfProfileClicked(); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
