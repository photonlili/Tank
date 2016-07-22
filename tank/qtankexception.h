#ifndef QTANKEXCEPTION_H
#define QTANKEXCEPTION_H

#include "qcdialog.h"

namespace Ui {
class QTankException;
}


enum {
    E_NOEXCEP = 0x0000,
    E_DOOROPEN = 0x0001,
    E_CORRROR = 0x0002,
    E_GUXIANERROR = 0x0004,
    E_SENSOR1ERR = 0x0008,

    E_SENSOR2ERR = 0x0010,
    E_JIGUANG1 = 0x0020,
    E_JIGUANG2 = 0x0040,
    E_VOLERR = 0x0080,
    E_POSION = 0x0100,
    E_MAINCOMM = 0x0200,

    E_RESET = 0x8000,
};

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
