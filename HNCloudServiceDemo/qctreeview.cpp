#include "qctreeview.h"
#include "ui_qctreeview.h"

QCTreeView::QCTreeView(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::QCTreeView)
{
    ui->setupUi(this);
}

QCTreeView::~QCTreeView()
{
    delete ui;
}
