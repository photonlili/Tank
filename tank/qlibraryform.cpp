#include "qlibraryform.h"
#include "ui_qlibraryform.h"

QLibraryForm::QLibraryForm(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QLibraryForm)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    connect(ui->tbv_lib->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentDBChanged(QModelIndex,QModelIndex)));
}

QLibraryForm::~QLibraryForm()
{
    delete ui;
}

void QLibraryForm::initAll()
{
    ui->tbv_lib->refresh();
    ui->tbv_lib->selectdb();
}

void QLibraryForm::on_btn_lib_select_clicked()
{
    QString db = ui->tbv_lib->currentdb();
    emit libSelected(db);
    accept();
}

void QLibraryForm::on_btn_lib_save_clicked()
{
    QFile::rename(QString("%1/%2.db").arg(DB_METHOD).arg(ui->tbv_lib->currentdb()),
                  QString("%1/%2.db").arg(DB_METHOD).arg(ui->le_lib_name->text()));
    ui->tbv_lib->setdbname(ui->le_lib_name->text());
}

void QLibraryForm::on_btn_lib_del_clicked()
{
    ui->tbv_lib->delDB();
}

void QLibraryForm::on_btn_lib_add_clicked()
{
    ui->tbv_lib->newDB();
}

void QLibraryForm::currentDBChanged(QModelIndex, QModelIndex)
{
    QString db = ui->tbv_lib->currentDBDisplayed();
    ui->le_lib_name->setText(db);
}

void QLibraryForm::on_btnClose_clicked()
{
    reject();
}
