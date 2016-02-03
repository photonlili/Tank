#include "hnupgradewidget.h"
#include "ui_hnupgradewidget.h"

HNUpgradeWidget::HNUpgradeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNUpgradeWidget)
{
    ui->setupUi(this);
}

HNUpgradeWidget::~HNUpgradeWidget()
{
    delete ui;
}
