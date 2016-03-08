#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:02:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HNEthenetDemo
TEMPLATE = app


SOURCES += main.cpp\
        hnethdemowidget.cpp \
    HNEthManager.cpp \
    qcdialog.cpp \
    qwifimodel.cpp \
    qwifipassform.cpp \
    qwifiview.cpp \
    qwifiwidget.cpp \
    qcomponent.cpp \
    qtankpublic.cpp \
    qcstandarditemmodel.cpp \
    qcpushbutton.cpp \
    qctableview.cpp \
    qcheaderview.cpp \
    hnmsgbox.cpp \
    qserialwarning.cpp \
    qcwidget.cpp

HEADERS  += hnethdemowidget.h \
    HNEthManager.h \
    qcdialog.h \
    qwifimodel.h \
    qwifipassform.h \
    qwifiview.h \
    qwifiwidget.h \
    qcomponent.h \
    qtankdefine.h \
    qtanklinux.h \
    qtankpublic.h \
    qtankgui.h \
    qcstandarditemmodel.h \
    qcpushbutton.h \
    qctableview.h \
    qcheaderview.h \
    hnmsgbox.h \
    qserialwarning.h \
    qcwidget.h

FORMS    += hnethdemowidget.ui \
    qcdialog.ui \
    qwifipassform.ui \
    qwifiview.ui \
    qwifiwidget.ui \
    qcpushbutton.ui \
    qctableview.ui \
    hnmsgbox.ui \
    qserialwarning.ui \
    qcwidget.ui

OTHER_FILES += \
    HNEthenetDemo.pro.user

RESOURCES += \
    theme.qrc
