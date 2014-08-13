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
    Common.cpp \
    control_payments.cpp \
    Database/waterdb.cpp \
    Forms/electricity.cpp \
    Forms/rubbish.cpp \
    Forms/water.cpp \
    Forms/gas.cpp \
    Database/electricitydb.cpp \
    Database/gasdb.cpp \
    Database/rubbishdb.cpp \
    Database/commondb.cpp \
    change_tariffs.cpp

HEADERS  += mainwindow.h \
    Common.h \
    dialog_input_new_value.h \
    control_payments.h \
    Common_Struct_data.h \
    Database/waterdb.h \
    Forms/electricity.h \
    Forms/rubbish.h \
    Forms/water.h \
    Forms/gas.h \
    Database/electricitydb.h \
    Database/gasdb.h \
    Database/rubbishdb.h \
    Database/commondb.h \
    Common_parameters.h \
    change_tariffs.h

FORMS    += mainwindow.ui \
    dialog_input_new_value.ui \
    control_payments.ui \
    Forms/electricity.ui \
    Forms/rubbish.ui \
    Forms/water.ui \
    Forms/gas.ui \
    change_tariffs.ui

CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    Readme.txt

