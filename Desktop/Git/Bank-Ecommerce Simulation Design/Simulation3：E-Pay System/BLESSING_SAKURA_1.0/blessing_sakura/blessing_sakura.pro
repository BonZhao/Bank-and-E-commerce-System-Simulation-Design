#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T21:02:44
#
#-------------------------------------------------

QT       += core gui\
         network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blessing_sakura
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    goods.cpp

HEADERS  += mainwindow.h \
    client.h \
    goods.h

FORMS    += mainwindow.ui

RESOURCES += \
    sakura.qrc
