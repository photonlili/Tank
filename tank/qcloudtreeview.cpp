#include "qcloudtreeview.h"
#include "ui_qcloudtreeview.h"

QCloudTreeView::QCloudTreeView(QWidget *parent) :
    QCTreeView(parent),
    ui(new Ui::QCloudTreeView)
{
    ui->setupUi(this);
    setHeaderHidden(true);
}

QCloudTreeView::~QCloudTreeView()
{
    delete ui;
}
