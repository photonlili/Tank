#ifndef HNMSGBOX_H
#define HNMSGBOX_H

#include "qcdialog.h"

namespace Ui {
class HNMsgBox;
}

class HNMsgBox : public QCDialog
{
    Q_OBJECT

public:
    explicit HNMsgBox(QWidget *parent = 0);
    ~HNMsgBox();

    static int warning(QWidget* parent = 0, QString content = "");
    static int tips(QWidget* parent = 0, QString content = "");

protected:
    int _warning(QString content);
    int _tips(QString content);

private:
    Ui::HNMsgBox *ui;
};

#endif // HNMSGBOX_H
