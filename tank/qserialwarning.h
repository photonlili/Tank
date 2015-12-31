#ifndef QSERIALWARNING_H
#define QSERIALWARNING_H

#include "qcdialog.h"

namespace Ui {
class QSerialWarning;
}

class QSerialWarning : public QCDialog
{
    Q_OBJECT

public:
    explicit QSerialWarning(QWidget *parent = 0);
    ~QSerialWarning();

private:
    Ui::QSerialWarning *ui;
};

#endif // QSERIALWARNING_H
