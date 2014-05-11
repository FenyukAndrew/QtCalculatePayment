#-------------------------------------------------
#
# Project created by QtCreator 2014-04-22T14:42:08
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    electricity.cpp \
    water.cpp \
    waterdb.cpp

HEADERS  += mainwindow.h \
    electricity.h \
    water.h \
    waterdb.h \
    Common.h

FORMS    += mainwindow.ui \
    electricity.ui \
    water.ui
