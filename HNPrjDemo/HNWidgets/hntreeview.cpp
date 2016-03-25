#include "hntreeview.h"
#include "ui_hntreeview.h"

HNTreeView::HNTreeView(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::HNTreeView)
{
    ui->setupUi(this);
}

HNTreeView::~HNTreeView()
{
    delete ui;
}
