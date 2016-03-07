#ifndef QLIBRARYFORM_H
#define QLIBRARYFORM_H

#include "qcdialog.h"
#include <QModelIndex>

namespace Ui {
class QLibraryForm;
}

class QLibraryForm : public QCDialog
{
    Q_OBJECT

public:
    explicit QLibraryForm(QWidget *parent = 0);
    ~QLibraryForm();

    void initAll();

signals:
    void libSelected(QString name);
    void libSelectedDisplayed(QString name);

private slots:
    void on_btn_lib_select_clicked();

    void on_btn_lib_save_clicked();

    void on_btn_lib_del_clicked();

    void on_btn_lib_add_clicked();

    void currentDBChanged(QModelIndex,QModelIndex);
    void on_btnClose_clicked();

private:
    Ui::QLibraryForm *ui;
};

#endif // QLIBRARYFORM_H
