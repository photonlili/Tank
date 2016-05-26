#ifndef WSNDIALOG_H
#define WSNDIALOG_H

#include <QDialog>

namespace Ui {
class WSNDialog;
}

class WSNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WSNDialog(QWidget *parent = 0);
    ~WSNDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::WSNDialog *ui;
};

#endif // WSNDIALOG_H
