#include "hnupgradewidget.h"
#include "ui_hnupgradewidget.h"
#include "qtankdefine.h"
#include <QTimer>
#include "qtankclient.h"

HNUpgradeWidget::HNUpgradeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNUpgradeWidget)
{
    ui->setupUi(this);
    ui->widgetBackup->setFixedSize(240, 30);
    ui->widgetBackup->setRange(0, 100);
    ui->widgetBackup->setValue(0);
    ui->widgetDown->setFixedSize(240, 30);
    ui->widgetDown->setRange(0, 100);
    ui->widgetDown->setValue(0);
    ui->widgetFugai->setFixedSize(240, 30);
    ui->widgetFugai->setRange(0, 100);
    ui->widgetFugai->setValue(0);
}

HNUpgradeWidget::~HNUpgradeWidget()
{
    delete ui;
}

void HNUpgradeWidget::initAll()
{
    ui->lbTip->setText(tr("Please don't close this computer! Upgrading..."));
    backup();
    download();
    restore();
    ui->lbTip->setText(tr("Upgrade success, Restarting..."));
    //system("reboot");
}

void HNUpgradeWidget::download()
{
    //开始下载过程
    ui->lbDown->setText(tr("Downloading..."));
    system("rm -f /DWINFile/upgrade/upgrade.tar.gz");
    m_cli = HNSingleClient();
    connect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetDown, SLOT(setValue(int)));
    connect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
    m_cli->sendDownDevFiles("/DWINFile/upgrade", "356", "upgrade.tar.gz");
}

void HNUpgradeWidget::downOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)), ui->widgetDown, SLOT(setValue(int)));
    disconnect(m_cli, SIGNAL(signalDownSucc()), this, SLOT(downOK()));
    ui->lbDown->setText(tr("Download Success"));
}

void HNUpgradeWidget::backup()
{
    //开始备份
    ui->lbBack->setText(tr("Backuping..."));
    ui->widgetBackup->setValue(24);
    system("rm -f /DWINFile/backup/backup.tar.gz");
    systemChild("tar czvf /DWINFile/backup/backup.tar.gz /DWINFile/tank");
    ui->widgetBackup->setValue(100);
    ui->lbBack->setText(tr("Backup Success"));
}

void HNUpgradeWidget::restore()
{
    ui->lbUpgrade->setText(tr("Restoring..."));
    systemChild("tar xzvf /DWINFile/upgrade/upgrade.tar.gz -C /");
    system("rm -f /DWINFile/upgrade/upgrade.tar.gz");
    ui->lbUpgrade->setText(tr("Restore Success..."));
}
