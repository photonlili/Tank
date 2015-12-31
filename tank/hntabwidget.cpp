#include "hntabwidget.h"
#include "ui_hntabwidget.h"

HNTabWidget::HNTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::HNTabWidget)
{
    ui->setupUi(this);
}

HNTabWidget::~HNTabWidget()
{
    delete ui;
}
