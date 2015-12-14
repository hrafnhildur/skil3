#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T16:29:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skil3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    computer.cpp \
    database.cpp \
    scientist.cpp \
    service.cpp

HEADERS  += mainwindow.h \
    computer.h \
    database.h \
    scientist.h \
    service.h

FORMS    += mainwindow.ui
