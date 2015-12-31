#ifndef QTANKSERIALPORT_H
#define QTANKSERIALPORT_H

#include <QSerialPort>
#include "qtankserialmessage.h"
#include "qtankpublic.h"

//生产部门使用这个串口操作机器
class QTankSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit QTankSerialPort(QObject *parent = 0);
    ~QTankSerialPort();

signals:
    void sigSerialUnlock();

public slots:

private slots:
    void readyReadData();
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void recvHandup(const QByteArray& l);
    void sendHandupAck();
    void recvClose(const QByteArray& l);
    void sendCloseAck();
    void recvWriteSerialNumber(const QByteArray& l);
    void sendWriteSerialNumberAck();
    void recvReadSerial(const QByteArray& l);
    void sendReadSerialAck();
    void recvWritePassword(const QByteArray& l);
    void sendWritePasswordAck();
    void recvReadPassword(const QByteArray& l);
    void sendReadPasswordAck();
    void sendExceptionAck();
private:
};

QTankSerialPort *HNSerialPort(QObject* parent = 0);

#endif // QTANKSERIALPORT_H
