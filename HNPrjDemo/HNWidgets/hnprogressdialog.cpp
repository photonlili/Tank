#include "hnprogressdialog.h"
#include "ui_hnprogressdialog.h"
#include "HNDefine.h"

HNProgressDialog::HNProgressDialog(QWidget *parent) :
    HNDialog(parent),
    ui(new Ui::HNProgressDialog)
{
    ui->setupUi(this);
    bar = ui->widgetBar;
    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));
}

HNProgressDialog::~HNProgressDialog()
{
    delete ui;
}

void HNProgressDialog::initAll()
{
    bar->setRange(0, 100);
    bar->setValue(0);
}

void HNProgressDialog::setValue(int value)
{
    bar->setValue(value);
}

