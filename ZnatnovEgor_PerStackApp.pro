QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application.cpp \
    ApplicationImplementation.cpp \
    Kernel/Pallette.cpp \
    QObserver.cpp \
    QPort.cpp \
    QRuntime.cpp \
    main.cpp \
    Interface/mainwindow.cpp \
    Except.cpp

HEADERS += \
    Application.h \
    ApplicationImplementation.h \
    Interface/mainwindow.h \
    Except.h \
    Kernel/ActionRequest.h \
    Kernel/MouseState.h \
    Kernel/Node.h \
    Kernel/Pallette.h \
    Kernel/PersistentStack.h \
    Kernel/PersistentStackController.h \
    Kernel/PersistentStackModel.h \
    QPort.h \
    QRuntime.h

FORMS += \
    Interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
