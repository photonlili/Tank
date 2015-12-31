#include "qclistview.h"
#include "ui_qclistview.h"

QCListView::QCListView(QWidget *parent) :
    QListView(parent),
    ui(new Ui::QCListView)
{
    ui->setupUi(this);
}

QCListView::~QCListView()
{
    delete ui;
}
