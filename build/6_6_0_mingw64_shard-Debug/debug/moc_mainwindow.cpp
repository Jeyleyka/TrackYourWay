/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "showLoginByClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "showModalWindow"
QT_MOC_LITERAL(4, 47, 14), // "onShowCalendar"
QT_MOC_LITERAL(5, 62, 13), // "onShowHistory"
QT_MOC_LITERAL(6, 76, 11), // "onShowLogin"
QT_MOC_LITERAL(7, 88, 17), // "loadTasksFromFile"
QT_MOC_LITERAL(8, 106, 15), // "saveTasksToFile"
QT_MOC_LITERAL(9, 122, 10), // "widgetText"
QT_MOC_LITERAL(10, 133, 22), // "countDaysAndListInFile"
QT_MOC_LITERAL(11, 156, 22), // "QPair<int,QStringList>"
QT_MOC_LITERAL(12, 179, 8), // "fileName"
QT_MOC_LITERAL(13, 188, 24), // "createInfoBlocksFromFile"
QT_MOC_LITERAL(14, 213, 19), // "QVector<InfoBlock*>"
QT_MOC_LITERAL(15, 233, 8), // "QWidget*"
QT_MOC_LITERAL(16, 242, 12), // "parentWidget"
QT_MOC_LITERAL(17, 255, 17), // "displayInfoBlocks"
QT_MOC_LITERAL(18, 273, 16) // "loadDataFromFile"

    },
    "MainWindow\0showLoginByClicked\0\0"
    "showModalWindow\0onShowCalendar\0"
    "onShowHistory\0onShowLogin\0loadTasksFromFile\0"
    "saveTasksToFile\0widgetText\0"
    "countDaysAndListInFile\0QPair<int,QStringList>\0"
    "fileName\0createInfoBlocksFromFile\0"
    "QVector<InfoBlock*>\0QWidget*\0parentWidget\0"
    "displayInfoBlocks\0loadDataFromFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x08 /* Private */,
      10,    1,   78,    2, 0x08 /* Private */,
      13,    2,   81,    2, 0x08 /* Private */,
      17,    0,   86,    2, 0x08 /* Private */,
      18,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    0x80000000 | 11, QMetaType::QString,   12,
    0x80000000 | 14, QMetaType::QString, 0x80000000 | 15,   12,   16,
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
        case 0: _t->showLoginByClicked(); break;
        case 1: _t->showModalWindow(); break;
        case 2: _t->onShowCalendar(); break;
        case 3: _t->onShowHistory(); break;
        case 4: _t->onShowLogin(); break;
        case 5: _t->loadTasksFromFile(); break;
        case 6: _t->saveTasksToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: { QPair<int,QStringList> _r = _t->countDaysAndListInFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPair<int,QStringList>*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVector<InfoBlock*> _r = _t->createInfoBlocksFromFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVector<InfoBlock*>*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->displayInfoBlocks(); break;
        case 10: _t->loadDataFromFile(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::showLoginByClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showLoginByClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
