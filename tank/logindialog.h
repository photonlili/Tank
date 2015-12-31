#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>
#include "qtankdefine.h"
#include "qtankpublic.h"
#include "mainwindow.h"

namespace Ui {
class QLoginDialog;
}

class QLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QLoginDialog(QWidget *parent = 0);
    ~QLoginDialog();

    void initAll();

signals:
    void signalStatus(int index);
private slots:
    void login();
    void initlanguage();

private:
    Ui::QLoginDialog *ui;
};

#endif // LOGINDIALOG_H
