#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T11:09:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (HnGui/HNWidgets.pri)

TARGET = wsn
TEMPLATE = app


SOURCES += main.cpp\
        wsndialog.cpp

HEADERS  += wsndialog.h

FORMS    += wsndialog.ui
