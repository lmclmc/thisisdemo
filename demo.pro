#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T13:40:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 console

SOURCES += \
        File/deflection.cpp \
        File/displacement.cpp \
        File/filewrapper.cpp \
        File/fopt.cpp \
        File/strain.cpp \
        UI/Editwidget.cpp \
        UI/graphwidget.cpp \
        UI/listwidget.cpp \
        UI/popupmenu.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        File/deflection.h \
        File/displacement.h \
        File/filewrapper.h \
        File/fopt.h \
        File/strain.h \
        UI/Editwidget.h \
        UI/graphwidget.h \
        UI/listwidget.h \
        UI/popupmenu.h \
        widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
