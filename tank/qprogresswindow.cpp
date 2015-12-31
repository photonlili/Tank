#include "qprogresswindow.h"
#include "ui_qprogresswindow.h"

QProgressWindow::QProgressWindow(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QProgressWindow)
{
    ui->setupUi(this);
    ui->pbar->setRange(0, 100);
    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));
    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SIGNAL(canceled()));
}

QProgressWindow::~QProgressWindow()
{
    delete ui;
}

void QProgressWindow::initAll()
{
    ui->pbar->setValue(0);
}

void QProgressWindow::setValue(int value)
{
    ui->pbar->setValue(value);
}

void QProgressWindow::cancel()
{
    reject();
}
