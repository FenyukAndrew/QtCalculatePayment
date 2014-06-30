#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T20:48:38
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCalculatePayment
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_input_new_value.cpp \
    electricity.cpp \
    water.cpp \
    waterdb.cpp \
    Common.cpp

HEADERS  += mainwindow.h \
    Common.h \
    dialog_input_new_value.h \
    electricity.h \
    water.h \
    waterdb.h

FORMS    += mainwindow.ui \
    dialog_input_new_value.ui \
    electricity.ui \
    water.ui

CONFIG += mobility
MOBILITY = 

