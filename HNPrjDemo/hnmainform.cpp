#include "hnmainform.h"
#include "ui_hnmainform.h"

HNMainForm::HNMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMainForm)
{
    ui->setupUi(this);

    HNTabBar* bar = (HNTabBar*)ui->tabWidget->cTabBar();
    bar->setTabPixmap(0, "://pictures/bt_setting.png", "://pictures/bt_setting_press.png");
    bar->setTabPixmap(1, "://pictures/bt_cloud.png", "://pictures/bt_cloud_press.png");

    HNClientInstance(this)->SendConnectMessage();
}

HNMainForm::~HNMainForm()
{
    delete ui;
}
