#ifndef QTANKPEERMESSAGE_H
#define QTANKPEERMESSAGE_H

#include <QDebug>

#define _PEER_HEAD 0XAA55
#define _PEER_TAIL 0XCC33

#define _PEER_CONC51       0x0000
#define _PEER_CONC51ACK    0x0001
#define _PEER_CMDNACK      0x0002

#define _PEER_HEAT         0x0003
#define _HEAT_STANDARD      0x02
#define _HEAT_RAMP          0x01
#define _HEAT_PRESS         0x03
#define _HEAT_EXTRACT       0x04
#define _HEAT_HOLD       0x05


#define _PEER_PAUSE                 0x0004
#define _PEER_STOP                  0x0005
#define _PEER_LEFT                  0x0006
#define _PEER_RIGHT                 0x0007
#define _PEER_SURROUND              0x0008
#define _PEER_STOPRUN                 0x0009

#define _PEER_STAT                   0x000A
#define _PEER_REPORTTANKNUM           0x000B
#define _PEER_DEBUG                    0x000C
#define _PEER_STIRSET               0x000D
#define _PEER_CALIBRATE               0x000E

#define _PEER_REPORTEXCEPTION         0x000F

#define _PEER_FACTORY                 0x0011

class QTankPeerMessage : public QObject
{
    Q_OBJECT
public:
    explicit QTankPeerMessage(QObject *parent = 0);

    const quint16& head() const { return m_Head; }
    void setHead(quint16 head) { m_Head = head; }
    const quint16& size() const { return m_Size; }
    void setSize(quint16 size) { m_Size = size; }
    //user
    const quint16& cmd() const { return m_Cmd; }
    void setCmd(quint16 cmd) { m_Cmd = cmd; }
    //user
    const QByteArray& data() const { return m_Data; }
    void setData(QByteArray& data) { m_Data = data; }
    const quint16& sum() const { return m_Sum; }
    void setSum(quint16 sum) { m_Sum = sum; }
    const quint16& tail() const { return m_Tail; }
    void setTail(quint16 tail) { m_Tail = tail; }

    static quint16 parseBlockSize(const QByteArray &netData);
    void parse(const QByteArray &netData);
    void translate();
    void pack(QByteArray& netData);

signals:

public slots:

private:
    quint16 m_Head;
    quint16 m_Size;
    quint16 m_Cmd;
    QByteArray m_Data;
    quint16 m_Sum;
    quint16 m_Tail;
};

QDebug operator<< (QDebug dbg, const QTankPeerMessage &c);

class QTankConnC51Struct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankConnC51Struct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankHeatStandardStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatStandardStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wTempture;
    quint16 wHold;
};

class QTankHeatPressStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatPressStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setPress(quint16 arg) {wPress = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wPress;
};

class QTankHeatRAMPStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatRAMPStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    quint8 stage() { return uStage; }
    quint8 vessel() { return uVessel; }
    quint16 ramp() { return wRamp; }
    quint16 press() { return wPress; }
    quint16 tempture() { return wTempture; }
    quint16 hold() { return wHold; }

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setRamp(quint16 arg) {wRamp = arg;}
    void setPress(quint16 arg) {wPress = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wRamp;
    quint16 wPress;
    quint16 wTempture;
    quint16 wHold;
};

class QTankHeatExtractStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatExtractStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint16 wTempture;
    quint16 wHold;
};

class QTankHeatHoldStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatHoldStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint16 wHold;
};

class QTankPauseStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankPauseStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankStopStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStopStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankCmd2C51Ack : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankCmd2C51Ack(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);
};

class QTankTurnLeftStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankTurnLeftStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};


class QTankTurnRightStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankTurnRightStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankSurroundStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankSurroundStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};


class QTankStopRunStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStopRunStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankStatStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStatStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankStatAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStatAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);

    qint16 tempture() { return tmpe; }
    qint16 pressure() { return press; }
    qint8 status() { return stat; }

private:
    qint16 tmpe;
    qint16 press;
    qint8 stat;
};


class QTankTankNumStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankTankNumStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};


class QTankTankNumAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankTankNumAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    quint8 num() { return m_num; }
    void parse(const QByteArray& l);
private:
    quint8 m_num;
};


class QTankResetAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankResetAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);
private:
};


class QTankFactoryStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankFactoryStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankFactoryAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankFactoryAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);
private:
};

class QTankDebugStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankDebugStruct(QObject *parent = 0) : QTankPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankDebugAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankDebugAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);
};


class QTankStirSetStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStirSetStruct(QObject *parent = 0) : QTankPeerMessage(parent){}
    void setSpeed(quint8 speed);
    void pack(QByteArray& l);
private:
    QByteArray d;
};

class QTankStirSetAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStirSetAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);
};


class QTankCalibrateStruct : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankCalibrateStruct(QObject *parent = 0) : QTankPeerMessage(parent){}
    void setParams(quint8 guangxian, quint8 hongwai, quint8 hongwai2,
                   quint8 yali, quint8 optional = 0);
    void pack(QByteArray& l);
private:
    QByteArray d;
};

class QTankCalibrateAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankCalibrateAck(QObject *parent = 0) : QTankPeerMessage(parent){}

    void parse(const QByteArray& l);

    quint8 guanxianRamp() { return ramp1; }
    quint8 hongwai1Ramp() { return ramp2; }
    quint8 hongwai2Ramp() { return ramp3; }
    quint8 press() { return press4; }
private:
    quint8 ramp1, ramp2, ramp3, press4;
};


class QTankExceptionAck : public QTankPeerMessage
{
    Q_OBJECT
public:
    explicit QTankExceptionAck(QObject *parent = 0) : QTankPeerMessage(parent){}
    quint16 status();
    void parse(const QByteArray& l);
private:
    quint16 st;
};

#endif // QTANKPEERMESSAGE_H
