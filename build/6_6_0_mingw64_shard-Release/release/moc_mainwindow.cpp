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
    QByteArrayData data[23];
    char stringdata0[330];
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
QT_MOC_LITERAL(7, 88, 12), // "onChangeIcon"
QT_MOC_LITERAL(8, 101, 17), // "loadTasksFromFile"
QT_MOC_LITERAL(9, 119, 15), // "saveTasksToFile"
QT_MOC_LITERAL(10, 135, 10), // "widgetText"
QT_MOC_LITERAL(11, 146, 22), // "countDaysAndListInFile"
QT_MOC_LITERAL(12, 169, 22), // "QPair<int,QStringList>"
QT_MOC_LITERAL(13, 192, 8), // "fileName"
QT_MOC_LITERAL(14, 201, 24), // "createInfoBlocksFromFile"
QT_MOC_LITERAL(15, 226, 19), // "QVector<InfoBlock*>"
QT_MOC_LITERAL(16, 246, 8), // "QWidget*"
QT_MOC_LITERAL(17, 255, 12), // "parentWidget"
QT_MOC_LITERAL(18, 268, 17), // "displayInfoBlocks"
QT_MOC_LITERAL(19, 286, 16), // "loadDataFromFile"
QT_MOC_LITERAL(20, 303, 8), // "saveIcon"
QT_MOC_LITERAL(21, 312, 8), // "filePath"
QT_MOC_LITERAL(22, 321, 8) // "loadIcon"

    },
    "MainWindow\0showLoginByClicked\0\0"
    "showModalWindow\0onShowCalendar\0"
    "onShowHistory\0onShowLogin\0onChangeIcon\0"
    "loadTasksFromFile\0saveTasksToFile\0"
    "widgetText\0countDaysAndListInFile\0"
    "QPair<int,QStringList>\0fileName\0"
    "createInfoBlocksFromFile\0QVector<InfoBlock*>\0"
    "QWidget*\0parentWidget\0displayInfoBlocks\0"
    "loadDataFromFile\0saveIcon\0filePath\0"
    "loadIcon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    1,   91,    2, 0x08 /* Private */,
      11,    1,   94,    2, 0x08 /* Private */,
      14,    2,   97,    2, 0x08 /* Private */,
      18,    0,  102,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,
      20,    1,  104,    2, 0x08 /* Private */,
      22,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    0x80000000 | 12, QMetaType::QString,   13,
    0x80000000 | 15, QMetaType::QString, 0x80000000 | 16,   13,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
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
        case 5: _t->onChangeIcon(); break;
        case 6: _t->loadTasksFromFile(); break;
        case 7: _t->saveTasksToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { QPair<int,QStringList> _r = _t->countDaysAndListInFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPair<int,QStringList>*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVector<InfoBlock*> _r = _t->createInfoBlocksFromFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVector<InfoBlock*>*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->displayInfoBlocks(); break;
        case 11: _t->loadDataFromFile(); break;
        case 12: _t->saveIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->loadIcon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
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
