#ifndef QCDIALOG_H
#define QCDIALOG_H

#include <QDialog>

namespace Ui {
class QCDialog;
}

class QCDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QCDialog(QWidget *parent = 0);
    ~QCDialog();

private:
    Ui::QCDialog *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QCDIALOG_H
