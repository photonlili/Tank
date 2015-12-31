#ifndef QNEWUSER_H
#define QNEWUSER_H

#include "qcdialog.h"

namespace Ui {
class QNewUser;
}

class QNewUser : public QCDialog
{
    Q_OBJECT

public:
    explicit QNewUser(QWidget *parent = 0);
    ~QNewUser();

    void initAll();
    void userInfo(QString& name, QString& password, QString& confirm, QString& authority, QString& comment);
private:
    Ui::QNewUser *ui;
};

#endif // QNEWUSER_H
