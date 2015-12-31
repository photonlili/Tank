#include "qopenlibrary.h"
#include "ui_qopenlibrary.h"
#include "qtankpublic.h"
#include "qtankdefine.h"
#include "qtankgui.h"

QUserLibraryDialog::QUserLibraryDialog(QWidget *parent) :
    QFileDialog(parent),
    ui(new Ui::QOpenLibrary)
{
    ui->setupUi(this);

    setFileMode(QFileDialog::ExistingFile);
    setViewMode(QFileDialog::List);
    setAcceptMode(QFileDialog::AcceptOpen);
    moveCenter(this);

}

QUserLibraryDialog::~QUserLibraryDialog()
{
    delete ui;
}

void QUserLibraryDialog::initAll()
{
    setDirectory(".");
    setWindowTitle(QString("Open %1 Library").arg(gUserName));
    QStringList filters;

    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM Library WHERE Creater = '%1'").arg(gUserName));
    if (query.next()) {
        filters << query.value(Lib_Name).toString();
    }
    query.finish();

    setFilters(filters);
}
