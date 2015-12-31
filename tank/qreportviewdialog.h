#ifndef QREPORTVIEWDIALOG_H
#define QREPORTVIEWDIALOG_H

#include "qcdialog.h"
#include "qtankgui.h"
#include "qcsqltablemodel.h"

namespace Ui {
class QReportViewDialog;
}

class QReportViewDialog : public QCDialog
{
    Q_OBJECT

public:
    explicit QReportViewDialog(QWidget *parent = 0);
    ~QReportViewDialog();

    //SerialNo;
    QString newReport(QString library, QString method);
    void endReport(QString serialNo, QString Exception,
                      QString stopReason, QByteArray& plot);
    void initAll(QString name);
    void printToPdf();
    void print();

private:
    Ui::QReportViewDialog *ui;
    QSqlDatabase m_db;
};

#endif // QREPORTVIEWDIALOG_H
