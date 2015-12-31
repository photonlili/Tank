#ifndef QWIFIPASSFORM_H
#define QWIFIPASSFORM_H

#include "qcdialog.h"

namespace Ui {
class QWIFIPassForm;
}

class QWIFIPassForm : public QCDialog
{
    Q_OBJECT

public:
    explicit QWIFIPassForm(QWidget *parent = 0);
    ~QWIFIPassForm();

    void setWifiName(QString name);

signals:
    void connectClicked(QString password);
private slots:
    void connectClicked();
    void btnEnabled(QString);

private:
    Ui::QWIFIPassForm *ui;
};

#endif // QWIFIPASSFORM_H
