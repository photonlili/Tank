#ifndef QEDITFORM_H
#define QEDITFORM_H

#include <QWidget>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QItemSelection>
#include <QTableView>
#include "qopenlibrary.h"
#include <QDataWidgetMapper>
#include "qlibraryform.h"
#include "qstagewidget.h"

namespace Ui {
class QEditForm;
}

class QEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit QEditForm(QWidget *parent = 0);
    ~QEditForm();

    void initAll();

signals:
    void signalSaved(int mid, int type, QString name);

public slots:
    void currentMethodChanged(QModelIndex, QModelIndex);

    void saveM();
    void delM();
    void newM();
    
    void initLanguage();

private slots:
    void libGetted(QString name);

    void on_btn_open_clicked();

    void on_spin_stage_valueChanged(int arg1);

    void on_btn_stage_clear_clicked();

    void on_btn_stage_del_clicked();

    void on_btn_stage_add_clicked();    
    void on_comboBox_method_type_currentIndexChanged(int index);

private:
    Ui::QEditForm *ui;

    QUserLibraryDialog* openLib;
    QStageWidget* tbvStage;
    QLibraryForm* libForm;
};

#endif // QEDITFORM_H
