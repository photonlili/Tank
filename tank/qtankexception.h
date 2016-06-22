#ifndef QTANKEXCEPTION_H
#define QTANKEXCEPTION_H

#include "qcdialog.h"

namespace Ui {
class QTankException;
}

/*
 * 串口报警 通讯报警 设备报警
 * 显示异常并且写入数据库
 *
 */
class QTankException : public QCDialog
{
    Q_OBJECT

public:
    explicit QTankException(QWidget *parent = 0);
    ~QTankException();

public slots:
    void newExcp(quint16 e);

private:
    Ui::QTankException *ui;
};

QTankException* HNSingleException(QWidget* parent = 0);

#endif // QTANKEXCEPTION_H
