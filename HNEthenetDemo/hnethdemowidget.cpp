#include "hnethdemowidget.h"
#include "ui_hnethdemowidget.h"
#include "HNEthManager.h"

HNEthDemoWidget::HNEthDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNEthDemoWidget)
{
    ui->setupUi(this);
    connect(HNEthManager::Instance(), SIGNAL(sigConnected()), this, SLOT(wifiConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(wifiDisConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanConnected()), this, SLOT(netChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanDisConnected()), this, SLOT(netChanged()));
}

HNEthDemoWidget::~HNEthDemoWidget()
{
    delete ui;
}

void HNEthDemoWidget::netChanged()
{
    QString netName;
    if("Wired Lan" == HNEthManager::Instance()->currentNetName())
    {
        netName = tr("Current:Wired Lan");
        ui->tableView->setEnabled(false);
    }
    else
    {
        netName = tr("Current:%1").arg(HNEthManager::Instance()->currentNetName());
        ui->tableView->setEnabled(true);
    }
    ui->label->setText(netName);
}

void HNEthDemoWidget::wifiConnected()
{
    ui->widget_wifi->setPixmap("://theme/basic/bk_wifi_connected.png");
    ui->widget_wifi->update();
}

void HNEthDemoWidget::wifiDisConnected()
{
    ui->widget_wifi->setPixmap("://theme/basic/bk_wifi_unconnected.png");
    ui->widget_wifi->update();
}

void HNEthDemoWidget::on_checkBox_stateChanged(int arg1)
{
    QSettings setting;
    setting.setValue("EnableDHCP", arg1);
    setting.sync();

    // 2 -3, 0 -1 这里存在浮点运算错误
    //pline() << bChecked << ~bChecked;
    HNEthManager::Instance()->setDHCP(arg1?true:false);

    //ui->lineEdit_ip->setDisabled(bChecked);
    //ui->lineEdit_mask->setDisabled(bChecked);
    //ui->lineEdit_gateway->setDisabled(bChecked);
    //ui->lineEdit_dns->setDisabled(bChecked);
}

void HNEthDemoWidget::on_pushButton_clicked()
{
    HNEthManager::Instance()->configIPAddress("", "", "", "");//ui->lineEdit_ip->text(), ui->lineEdit_mask->text(),
                                              //ui->lineEdit_gateway->text(), ui->lineEdit_dns->text());
}
