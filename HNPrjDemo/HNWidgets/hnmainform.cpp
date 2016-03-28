#include "hnmainform.h"
#include "ui_hnmainform.h"

HNMainForm::HNMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMainForm)
{
    ui->setupUi(this);
}

HNMainForm::~HNMainForm()
{
    delete ui;
}
