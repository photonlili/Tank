#include "hnupgradewidget.h"
#include "ui_hnupgradewidget.h"
#include "qtankdefine.h"
#include <QTimer>
#include "qtankclient.h"
#include "qtankdefine.h"
#include "qtanklinux.h"

void QBackupLocalThread::run()
{
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Backuping...")));
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 12));
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 40));
#ifdef __MIPS_LINUX__
    system("tar czvf ./tmp/backup.tar.gz /DWINFile/tank");
#else
    system("tar czvf ./tmp/backup.tar.gz tank");
#endif
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 100));
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Success")));
    QMetaObject::invokeMethod(parent(), "download");
}

void QUpgradeThread::run()
{
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Progressing...")));
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 40));
#ifdef __MIPS_LINUX__
    system("tar xzvf ./tmp/upgrade.tar.gz -C /");
#else
    system("tar xzvf ./tmp/upgrade.tar.gz -C tmp");
#endif
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 60));
    system("rm -f ./tmp/upgrade.tar.gz ./tmp/backup.tar.gz");
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 100));
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Success")));
    QMetaObject::invokeMethod(parent(), "restart");
}

HNUpgradeWidget::HNUpgradeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNUpgradeWidget)
{
    ui->setupUi(this);

    QList<QLabel *> lb = this->findChildren<QLabel *>();
    foreach (QLabel * label, lb) {
        label->setForegroundRole(QPalette::BrightText);
    }

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(restart()));

    ui->lbUpgrade->setFixedWidth(300);
    ui->widgetUpgrade->setFixedSize(240, 20);
    ui->widgetUpgrade->setRange(0, 100);
    ui->widgetUpgrade->setValue(0);

    m_backupT = new QBackupLocalThread(this);
    m_upgradeT = new QUpgradeThread(this);
}

HNUpgradeWidget::~HNUpgradeWidget()
{
    delete ui;
}

void HNUpgradeWidget::initAll()
{
    system("mkdir tmp & rm -f tmp/upgrade.tar.gz");
    //检查版本更新信息
    //检查完毕
    m_backupT->start();
}

void HNUpgradeWidget::setText(QString text)
{
    ui->lbUpgrade->setText(text);
}

void HNUpgradeWidget::setValue(int value)
{
    ui->widgetUpgrade->setValue(value);
}

void HNUpgradeWidget::download()
{
    //开始下载过程
    ui->lbUpgrade->setText(tr("Downloading..."));
    m_cli = HNSingleClient(this);
    connect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetUpgrade, SLOT(setValue(int)));
    connect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
    m_cli->sendDownDevFiles("./tmp", "356", "upgrade.tar.gz");
}

void HNUpgradeWidget::downOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetUpgrade, SLOT(setValue(int)));
    disconnect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
    ui->lbUpgrade->setText(tr("Success"));
    m_upgradeT->start();
}

void HNUpgradeWidget::restart()
{
    static int i = 6;
    if(i == 0) {
#ifdef __MIPS_LINUX__
        system("reboot");
#endif
        timer->stop();
        return;
    }
    i--;
    ui->lbUpgrade->setText(tr("Upgrade success, Restarting... %1").arg(i));
    timer->start(1000);
}
