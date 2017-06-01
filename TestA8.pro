#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T08:49:58
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestA8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GPIO/GPIOClass.cpp

HEADERS  += mainwindow.h \
    GPIO/GPIOClass.h

FORMS    += mainwindow.ui

DISTFILES += \
    images/ball_gray.png \
    images/ball_green.png \
    images/ball_red.png \
    images/ball_yellow.png

RESOURCES += \
    resource.qrc

INSTALLS        = target
target.files    = TestA8
target.path     = /home/pi/work/cross/TestA8
