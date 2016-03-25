#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

QT       += core gui network sql
CONFIG += serialport
DEFINES += _TTY_POSIX_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HNWidgets
TEMPLATE = app

INCLUDEPATH += .

SOURCES += main.cpp\
        tempwidget.cpp \
    hncheckbox.cpp \
    HNDefine.cpp \
    hndialog.cpp \
    HNEthManager.cpp \
    hnheaderview.cpp \
    HNInput.cpp \
    hnlistview.cpp \
    hnmsgbox.cpp \
    hnprinter.cpp \
    hnprogressbar.cpp \
    hnpushbutton.cpp \
    hnradiobutton.cpp \
    hntabbar.cpp \
    hntableview.cpp \
    hntabwidget.cpp \
    hntabwidgetb.cpp \
    hntreeview.cpp \
    hnwidget.cpp \
    hnwifimodel.cpp \
    hnwifiview.cpp \
    hnwifiwidget.cpp \
    qcpdocumentobject.cpp \
    qcustomplot.cpp \
    templatewidget.cpp \
    hnclient.cpp \
    hnclientmessage.cpp \
    hncloudform.cpp \
    hncloudlocalmodel.cpp \
    hncloudlocaltreewidget.cpp \
    hncloudmodel.cpp \
    hncloudtreeview.cpp \
    hncloudtreewidget.cpp \
    hnexceptionmodel.cpp \
    hnexceptionview.cpp \
    hnexceptionwidget.cpp \
    HNLineEditWithSearch.cpp \
    hnpeermessage.cpp \
    hnpeerport.cpp \
    hnplayermodel.cpp \
    hnplayerwidget.cpp \
    hnpluginwatcher.cpp \
    hnprogressdialog.cpp \
    hnserialmessage.cpp \
    hnserialport.cpp \
    hnserver.cpp \
    hnsqltablemodel.cpp \
    hnstandarditemmodel.cpp \
    hnsyseventmodel.cpp \
    hnsyseventview.cpp \
    hnsyseventwidget.cpp \
    hnupgradewidget.cpp \
    hnpassworddialog.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    hnprintpreviewdialog.cpp

HEADERS  += tempwidget.h \
    hncheckbox.h \
    HNDefine.h \
    hndialog.h \
    HNEthManager.h \
    hngui.h \
    hngui-qt.h \
    hnheaderview.h \
    HNInput.h \
    hnlinux.h \
    hnlistview.h \
    hnmsgbox.h \
    hnprinter.h \
    hnprogressbar.h \
    HNPub.h \
    hnpushbutton.h \
    hnradiobutton.h \
    hntabbar.h \
    hntableview.h \
    hntabwidget.h \
    hntabwidgetb.h \
    hntreeview.h \
    hnwidget.h \
    hnwifimodel.h \
    hnwifiview.h \
    hnwifiwidget.h \
    qcpdocumentobject.h \
    qcustomplot.h \
    templatewidget.h \
    hnclient.h \
    hnclientmessage.h \
    hncloudform.h \
    hncloudlocalmodel.h \
    hncloudlocaltreewidget.h \
    hncloudmodel.h \
    hncloudtreeview.h \
    hncloudtreewidget.h \
    hnexceptionmodel.h \
    hnexceptionview.h \
    hnexceptionwidget.h \
    HNLineEditWithSearch.h \
    hnpeermessage.h \
    hnpeerport.h \
    hnplayermodel.h \
    hnplayerwidget.h \
    hnpluginwatcher.h \
    hnprogressdialog.h \
    hnserialmessage.h \
    hnserialport.h \
    hnserver.h \
    hnsqltablemodel.h \
    hnstandarditemmodel.h \
    hnsyseventmodel.h \
    hnsyseventview.h \
    hnsyseventwidget.h \
    hnupgradewidget.h \
    hnversion.h \
    hnpassworddialog.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    hnprintpreviewdialog.h

FORMS    += tempwidget.ui \
    hncheckbox.ui \
    hndialog.ui \
    HNInput.ui \
    hnlistview.ui \
    hnmsgbox.ui \
    hnprogressbar.ui \
    hnpushbutton.ui \
    hnradiobutton.ui \
    hntableview.ui \
    hntabwidget.ui \
    hntabwidgetb.ui \
    hntreeview.ui \
    hnwidget.ui \
    hnwifiview.ui \
    hnwifiwidget.ui \
    templatewidget.ui \
    hncloudform.ui \
    hncloudlocaltreewidget.ui \
    hncloudtreeview.ui \
    hncloudtreewidget.ui \
    hnexceptionview.ui \
    hnexceptionwidget.ui \
    hnplayerwidget.ui \
    hnprogressdialog.ui \
    hnsyseventview.ui \
    hnsyseventwidget.ui \
    hnupgradewidget.ui \
    hnpassworddialog.ui \
    hnprintpreviewdialog.ui

OTHER_FILES += \
    HNWidgets.pro.user \
    HNWidgets2.pri \
    version.rc \
    HNWidgets.pri
