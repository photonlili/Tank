#include "hnloginform.h"
#include "ui_hnloginform.h"

HNLoginForm::HNLoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNLoginForm)
{
    ui->setupUi(this);
}

HNLoginForm::~HNLoginForm()
{
    delete ui;
}
