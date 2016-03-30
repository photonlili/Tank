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
    setFixedWidth(260);
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
    ui->label->setText(tr("Progressing... %1%").arg(value));
    bar->setValue(value);
}

