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
    system("tar czvf ./tmp/backup.tar.gz /HNApp/tank");
#else
    system("tar czvf ./tmp/backup.tar.gz tank");
#endif
    QMetaObject::invokeMethod(parent(), "setValue", Q_ARG(int, 100));
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Success")));
    QMetaObject::invokeMethod(parent(), "download");
}

void QUpgradeThread::run()
{
    QMetaObject::invokeMethod(parent(), "setText", Q_ARG(QString, tr("Upgrading...")));
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
    ui->widgetUpgrade->setFixedSize(600, 30);
    ui->widgetUpgrade->setRange(0, 100);
    ui->widgetUpgrade->setValue(0);

    m_backupT = new QBackupLocalThread(this);
    m_upgradeT = new QUpgradeThread(this);

    m_cli = HNSingleUpgradeClient(this);
    connect(m_cli, SIGNAL(connected()), this, SLOT(logined()));
    connect(m_cli, SIGNAL(signalCheckVersionResult()), this, SLOT(versionR()));
    connect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetUpgrade, SLOT(setValue(int)));
    connect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
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
    ui->lbUpgrade->setText(tr("Checking version..."));
    m_cli->SendConnectMessage();
}

void HNUpgradeWidget::logined()
{
    m_newSoftwareID = "-1";
    ui->tbVersion->clear();
    m_cli->sendCheckVersion();
}

void HNUpgradeWidget::versionR()
{
    QTCheckVersionResult t = m_cli->GetVersionResult();
    if(m_newSoftwareID == "-1")
    {
        pline() << "cur";

        ui->tbVersion->append(tr("Version:%1").arg(t.m_version));
        ui->tbVersion->append(tr("Explain:%1").arg(t.m_Explain));
        ui->tbVersion->append(tr("ReleaseStatus:%1").arg(t.m_ReleaseStatus));
        ui->tbVersion->append(tr("ReleaseDate:%1").arg(t.m_ReleaseDate));
        ui->tbVersion->append(tr("FileMD5:%1").arg(t.m_FileMD5));
        ui->tbVersion->append(tr("FileSize:%1").arg(t.m_FileSize));

        m_newSoftwareID = t.m_NewSoftwareID;
        if(t.m_NewSoftwareID == "0")
        {
            ui->lbUpgrade->setText(tr("This is latest version."));
            return;
        }
        m_cli->sendCheckNewVersion();
    }
    else
    {
        pline() << "new";
        ui->tbVersion->append(tr("------------------------------------"));
        ui->tbVersion->append(tr("FileName:%1").arg(t.m_FileName));
        ui->tbVersion->append(tr("Version:%1").arg(t.m_version));
        ui->tbVersion->append(tr("Explain:%1").arg(t.m_Explain));
        ui->tbVersion->append(tr("ReleaseStatus:%1").arg(t.m_ReleaseStatus));
        ui->tbVersion->append(tr("ReleaseDate:%1").arg(t.m_ReleaseDate));
        ui->tbVersion->append(tr("FileMD5:%1").arg(t.m_FileMD5));
        ui->tbVersion->append(tr("FileSize:%1").arg(t.m_FileSize));
        ui->lbUpgrade->setText(tr("Found new version."));
    }
}

void HNUpgradeWidget::on_btnDown_clicked()
{
    ui->lbUpgrade->setText(tr("Downloading..."));
    m_cli->sendDownUpgradeFile("./tmp", m_newSoftwareID, "upgrade.tar.gz");
}

void HNUpgradeWidget::downOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetUpgrade, SLOT(setValue(int)));
    disconnect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
    ui->lbUpgrade->setText(tr("Download success"));
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

void HNUpgradeWidget::on_btnCancel_clicked()
{
    m_cli->SendDisConnectFromHost();
    emit sigCancelUpgrade();
}
