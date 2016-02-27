#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "qtankpublic.h"
#include <QFile>
#include <QSettings>
#include <QIcon>
#include <QTimer>
#include <QDateTime>
#include "qctabbar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_appname->setForegroundRole(QPalette::BrightText);
    ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));
    ui->label_time->setForegroundRole(QPalette::BrightText);
    ui->label_user->setForegroundRole(QPalette::BrightText);
    ui->label->setForegroundRole(QPalette::BrightText);
    connect(ui->tab_set, SIGNAL(showDebugWindow(int)),
            ui->tab_dispel, SLOT(showDebugWindow(int)));
    connect(ui->tab_dispel, SIGNAL(signalUpdateLabReport()),
            ui->tab_cloud, SLOT(slotUpdateLabReport()));
    connect(ui->tab_set, SIGNAL(sigUpgrade()), this,  SIGNAL(sigUpgrade()));
    connect(ui->tab_set, SIGNAL(changeLanguage()), this,  SIGNAL(changeLanguage()));
    connect(ui->tab_set, SIGNAL(changeLanguage()), this,  SLOT(initLanuage()));
    connect(ui->tab_user, SIGNAL(setTheme()), this, SLOT(initTheme()));
    connect(ui->tab_user, SIGNAL(setPic()), this, SLOT(initPic()));
    connect(ui->tab_user, SIGNAL(signalLogout()), this, SIGNAL(signalLogout()));
    //这个静态句柄，会引发信号和槽的参数不能被moc编译器识别。运行时找不到带参数的信号和槽。
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(wifiDisConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigConnecting()), this, SLOT(wifiConnecting()));
    connect(HNEthManager::Instance(), SIGNAL(sigConnected()), this, SLOT(wifiConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(wifiDisConnected()));

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(timerSetTime()) );
    //connect( timer, SIGNAL(timeout()), ui->tab_set, SLOT(timerSetTime()) );
    timer->setSingleShot(false);
    timer->start( 1000 ); // 1s触发定时器
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAll()
{
    ui->tab_set->initAll();
    ui->tab_dispel->initAll();
    ui->tab_edit->initAll();
    ui->tab_user->initAll();
    ui->label_user->setText(gUserName);
}

void MainWindow::slotSerialLocked()
{
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_set->slotSerialLock();
}

void MainWindow::slotSerialUnlocked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->tab_set->slotSerialUnlock();
}

void MainWindow::initLanuage()
{
    ui->retranslateUi(this);
    ui->tab_dispel->initLanguage();
    ui->tab_edit->initLanguage();
    ui->tab_set->initLanguage();
    ui->tab_cloud->chageLanguage();
    ui->tab_help->initLanguage();
    ui->tab_user->initLanguage();
    ui->label_user->setText(gUserName);
}

void MainWindow::initTheme()
{
    QSettings setting;
    QString themeName = setting.value(QString("/%1/Theme").arg(gUserName)).toString();
    if(themeName.isEmpty())
        themeName = "blue";

    //pline() << QDateTime::currentDateTime();
    QFile styleFile(QString(":/theme/%1/theme.qss").arg(themeName));
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();
    //pline() << QDateTime::currentDateTime();

    themeName = "basic";
    QCTabBar* bar = (QCTabBar*)ui->tabWidget->cTabBar();
    bar->setTabPixmap(0, QString("://theme/%1/bt_dispel.png").arg(themeName), QString("://theme/%1/bt_dispel_press.png").arg(themeName));
    bar->setTabPixmap(1, QString("://theme/%1/bt_edit.png").arg(themeName), QString("://theme/%1/bt_edit_press.png").arg(themeName));
    bar->setTabPixmap(2, QString("://theme/%1/bt_setting.png").arg(themeName), QString("://theme/%1/bt_setting_press.png").arg(themeName));
    bar->setTabPixmap(3, QString("://theme/%1/bt_help.png").arg(themeName), QString("://theme/%1/bt_help_press.png").arg(themeName));
    bar->setTabPixmap(4, QString("://theme/%1/bt_user.png").arg(themeName), QString("://theme/%1/bt_user_press.png").arg(themeName));
    bar->setTabPixmap(5, QString("://theme/%1/bt_cloud.png").arg(themeName), QString("://theme/%1/bt_cloud_press.png").arg(themeName));
}

void MainWindow::initPic()
{
    QSettings setting;
    QString picName = setting.value(QString("/%1/Pic").arg(gUserName)).toString();
    if(picName.isEmpty())
        picName = "user";
    ui->widget_pic->setPixmap(QString("://theme/basic/bk_%1_normal.png").arg(picName));
    ui->widget_pic->update();
}

void MainWindow::wifiConnected()
{
    ui->widget_wifi->setPixmap("://theme/basic/bk_wifi_connected.png");
    ui->widget_wifi->update();
}

void MainWindow::wifiDisConnected()
{
    ui->widget_wifi->setPixmap("://theme/basic/bk_wifi_unconnected.png");
    ui->widget_wifi->update();
}

void MainWindow::wifiConnecting()
{
    ui->widget_wifi->setPixmap("://theme/basic/bk_wifi_connecting.png");
    ui->widget_wifi->update();
}

void MainWindow::timerSetTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    //pline() << dt.currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    ui->label_time->setText(dt.toString("yyyy/MM/dd hh:mm:ss"));
}
