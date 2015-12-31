#include "qexceptionview.h"
#include "ui_qexceptionview.h"

QExceptionView::QExceptionView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QExceptionView)
{
    ui->setupUi(this);
}

QExceptionView::~QExceptionView()
{
    delete ui;
}
