QT       += core gui
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = untitled1
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calendarwidget.cpp \
    changeusernamewnd.cpp \
    dayofweekapi.cpp \
    infoblock.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    modalwindow.cpp \
    qwraplayout.cpp \
    schedulewidget.cpp \
    taskwidget.cpp \
    welcomewnd.cpp

HEADERS += \
    calendarwidget.h \
    changeusernamewnd.h \
    dayofweekapi.h \
    infoblock.h \
    libs.h \
    login.h \
    mainwindow.h \
    modalwindow.h \
    qwraplayout.h \
    schedulewidget.h \
    taskwidget.h \
    welcomewnd.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
