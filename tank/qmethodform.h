#ifndef QMETHODFORM_H
#define QMETHODFORM_H

#include "qcdialog.h"

namespace Ui {
class QMethodForm;
}

class QMethodForm : public QCDialog
{
    Q_OBJECT

public:
    explicit QMethodForm(QWidget *parent = 0);
    ~QMethodForm();

    enum {
        Working = 2,
    };

    void initAll();

    QString currentLibrary();
    QString currentMethodName();
    int currentMethodType();

signals:
    void tellMethod(QString name);
    void tellLibrary(QString name);
    void tellType(QString type);
    void selMethod(QString dbname, int id);

public slots:
    void libChanged();
    void methodChanged();

private slots:
    void on_btn_up_clicked();

    void on_btn_down_clicked();

    void on_btn_sure_clicked();

    void on_le_search_btnClicked();

private:
    Ui::QMethodForm *ui;
};

#endif // QMETHODFORM_H
