#include "qcdatetime.h"
#include "ui_qcdatetime.h"

QCDateTime::QCDateTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCDateTime)
{
    ui->setupUi(this);
}

QCDateTime::~QCDateTime()
{
    delete ui;
}
