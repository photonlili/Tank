#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T11:09:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (HnGui/HnGui.pri)

TARGET = wsn
TEMPLATE = app

target.path = /HNApp

INSTALLS += target

SOURCES += main.cpp\
        wsndialog.cpp \
    hnapp.cpp

HEADERS  += wsndialog.h \
    hnapp.h

FORMS    += wsndialog.ui
