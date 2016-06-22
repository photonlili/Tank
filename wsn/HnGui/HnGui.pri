#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

QT       += core gui network sql

CONFIG += serialport

DEFINES += _TTY_POSIX_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

QT_KIT = $$(QKIT)

message(HnGui $${QT_KIT} )

#MIPS __MIPS_LINUX__
#PC64 __LINUX64__

equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else {
    DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

SOURCES += \
	$$PWD/hncheckbox.cpp \
    $$PWD/HNDefine.cpp \
    $$PWD/hndialog.cpp \
    $$PWD/HNEthManager.cpp \
    $$PWD/hnheaderview.cpp \
    $$PWD/hnlistview.cpp \
    $$PWD/hnprinter.cpp \
    $$PWD/hnprogressbar.cpp \
    $$PWD/hnpushbutton.cpp \
    $$PWD/hnradiobutton.cpp \
    $$PWD/hntabbar.cpp \
    $$PWD/hntableview.cpp \
    $$PWD/hntabwidget.cpp \
    $$PWD/hntabwidgetb.cpp \
    $$PWD/hntreeview.cpp \
    $$PWD/hnwidget.cpp \
    $$PWD/qcpdocumentobject.cpp \
    $$PWD/qcustomplot.cpp \
    $$PWD/hnclient.cpp \
    $$PWD/hnclientmessage.cpp \
    $$PWD/HNLineEditWithSearch.cpp \
    $$PWD/hnpeermessage.cpp \
    $$PWD/hnpeerport.cpp \
	$$PWD/hnplayer.cpp \
    $$PWD/hnpluginwatcher.cpp \
    $$PWD/hnserialmessage.cpp \
    $$PWD/hnserialport.cpp \
    $$PWD/hnserver.cpp \
    $$PWD/hntablemodel.cpp \
    $$PWD/hnstandarditemmodel.cpp \
    $$PWD/qdevicewatcher.cpp \
    $$PWD/qdevicewatcher_linux.cpp \
    $$PWD/HNPreviewWidget.cpp \
    $$PWD/dmmu.c \
    $$PWD/hnmptablewidget.cpp \
    $$PWD/hntablewidget.cpp \
    $$PWD/hngraphicsscene.cpp \
    $$PWD/hngraphicsitem.cpp \
    $$PWD/hngraphicsview.cpp \
    $$PWD/hnword.cpp \
    $$PWD/hnreport.cpp \
    $$PWD/hnobjectfactory.cpp \
	$$PWD/hntreemodel.cpp \
	$$PWD/hnfilesystem.cpp \
	$$PWD/hntreewidget.cpp

HEADERS  += \
	$$PWD/hncheckbox.h \
    $$PWD/HNDefine.h \
    $$PWD/hndialog.h \
    $$PWD/HNEthManager.h \
    $$PWD/hngui.h \
    $$PWD/hngui-qt.h \
    $$PWD/hnheaderview.h \
    $$PWD/hnlinux.h \
    $$PWD/hnlistview.h \
    $$PWD/hnprinter.h \
    $$PWD/hnprogressbar.h \
    $$PWD/HNPub.h \
    $$PWD/hnpushbutton.h \
    $$PWD/hnradiobutton.h \
    $$PWD/hntabbar.h \
    $$PWD/hntableview.h \
    $$PWD/hntabwidget.h \
    $$PWD/hntabwidgetb.h \
    $$PWD/hntreeview.h \
    $$PWD/hnwidget.h \
    $$PWD/qcpdocumentobject.h \
    $$PWD/qcustomplot.h \
    $$PWD/hnclient.h \
    $$PWD/hnclientmessage.h \
    $$PWD/HNLineEditWithSearch.h \
    $$PWD/hnpeermessage.h \
    $$PWD/hnpeerport.h \
	$$PWD/hnplayer.h \
    $$PWD/hnpluginwatcher.h \
    $$PWD/hnserialmessage.h \
    $$PWD/hnserialport.h \
    $$PWD/hnserver.h \
    $$PWD/hntablemodel.h \
    $$PWD/hnstandarditemmodel.h \
    $$PWD/qdevicewatcher.h \
    $$PWD/qdevicewatcher_p.h \
    $$PWD/dmmu.h \
    $$PWD/graphics.h \
    $$PWD/hal.h \
    $$PWD/HNPreviewWidget.h \
    $$PWD/jz_cim.h \
    $$PWD/hnmptablewidget.h \
    $$PWD/hntablewidget.h \
    $$PWD/hngraphicsscene.h \
    $$PWD/hngraphicsitem.h \
    $$PWD/hngraphicsview.h \
    $$PWD/hnword.h \
    $$PWD/hnreport.h \
	$$PWD/version.h \
	$$PWD/hnobjectfactory.h \
	$$PWD/hntreemodel.h \
	$$PWD/hnfilesystem.h \
	$$PWD/hntreewidget.h

FORMS    += \
	$$PWD/hncheckbox.ui \
    $$PWD/hndialog.ui \
    $$PWD/hnlistview.ui \
    $$PWD/hnprogressbar.ui \
    $$PWD/hnpushbutton.ui \
    $$PWD/hnradiobutton.ui \
    $$PWD/hntableview.ui \
    $$PWD/hntabwidget.ui \
    $$PWD/hntabwidgetb.ui \
    $$PWD/hntreeview.ui \
    $$PWD/hnwidget.ui \
    $$PWD/HNPreviewWidget.ui \
    $$PWD/hnmptablewidget.ui \
    $$PWD/hntablewidget.ui \
	$$PWD/hntreewidget.ui
