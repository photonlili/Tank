#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T15:34:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(HNWidgets/HNWidgets.pri)

TARGET = HNPrjDemo
TEMPLATE = app


SOURCES += main.cpp\
        hnframe.cpp

HEADERS  += hnframe.h

FORMS    += hnframe.ui
