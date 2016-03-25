#include "hnframe.h"
#include "ui_hnframe.h"
#include "HNPub.h"

HNFrame::HNFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNFrame)
{
    ui->setupUi(this);
}

HNFrame::~HNFrame()
{
    delete ui;
}
