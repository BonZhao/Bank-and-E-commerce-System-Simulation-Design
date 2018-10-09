#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T10:40:10
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BANK_STEAM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bank_backend.cpp \
    card.cpp

HEADERS  += mainwindow.h \
    bank_backend.h \
    card.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    background_bank.qrc
