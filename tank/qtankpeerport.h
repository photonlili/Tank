#ifndef QTANKPEERPORT_H
#define QTANKPEERPORT_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qtankpeermessage.h"
#include "qtankpublic.h"

//屏通过这个类和单片机进行通信
class QTankPeerPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit QTankPeerPort(QObject *parent = 0);
    ~QTankPeerPort();

    void setHeatParam(quint8 stage, quint8 vessel, quint16 ramp, quint16 press, quint16 hold);
    void sendMsgConnectToC51();
    void sendMsgHeatPress(quint8 stage, quint8 vessel, quint16 press);
    void sendMsgHeatStandard(quint8 stage, quint8 vessel, quint16 tempture, quint16 hold);
    void sendMsgHeatRAMP(quint8 stage, quint8 vessel, quint16 ramp, quint16 press, quint16 tempture, quint16 hold);
    void sendMsgHeatExtract(quint8 stage, quint16 tempture, quint16 hold);
    void sendMsgPause();
    void sendMsgStop();
    void sendLeft();
    void sendRight();
    void sendSurround();
    void sendStopTurn();
    void sendStat();

    void sendDebug();
    void sendStirSet(quint8 speed);
    void sendCalibrate(quint8 guangxian, quint8 hongwai, quint8 hongwai2, quint8 yali, quint8 option = 0);

signals:
    void sigRecvMsg(QByteArray msg);
    void sigPeerException(quint16 eCode);
    void sigPeerReset();
    void sigStat(quint16 temp, quint16 press, quint8 stat);
    void sigTankNum(quint8 num);
    void sigCaliAck(quint16 temp, quint16 temp2, quint16 temp3, quint16 pressure);
    void sigDebug(QByteArray d);
private slots:
    void sendConnectToC51();
    void sendHeatPress();
    void sendHeatStandard();
    void sendHeatRAMP();
    void sendHeatExtract();
    void sendPause();
    void sendStop();

private slots:
    void readyReadData();
    void updateProgress(qint64);
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void SendSerialMessage();
private:
    void recvCmdAck(const QByteArray &l);
    void recvCmdNAck(const QByteArray &l);
    void recvStatAck(const QByteArray &l);
    void recvTankNumAck(const QByteArray &l);
    void recvDebugAck(const QByteArray &l);
    void recvCalibrateAck(const QByteArray &l);
    void recvExceptionAck(const QByteArray &l);

    enum{
        Heat_Standart,
        Heat_Press,
        Heat_Ramp,
        Heat_Extract,
    };

    QTimer* timer;
    quint16 m_cmdCount;
    quint16 m_msgType;
    quint16 m_heatType;
    QTankHeatRAMPStruct m_heat;
};

QTankPeerPort *HNPeerPort(QObject* parent = 0);

#endif // QTANKPEERPORT_H
