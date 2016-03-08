#include "qtankpeerport.h"
#include "qtankpublic.h"
#include "qtankpeermessage.h"
#include "qcomponent.h"

#define MAX_CONNCOUNT 5 //(+1)
#define MAX_SERIALTIME 1000

QTankPeerPort::QTankPeerPort(QObject *parent) :
    QSerialPort(parent)
{
#ifdef __MIPS_LINUX__
    QString portName("/dev/ttyS0");
#else
    QString portName("/dev/ttyS3");
#endif
    setPortName(portName);
    setBaudRate(QSerialPort::Baud57600);
    setDataBits(QSerialPort::Data8);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);

    if(open(QIODevice::ReadWrite)) //Open Port dev.
        pline() << QString("serial port %1 open success!").arg(portName);
    else
        pline() << QString("serial port %1 open failed! errcode =").arg(portName) << errorString();
    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)), Qt::QueuedConnection );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()), Qt::QueuedConnection );
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(SendSerialMessage()));

    m_cmdCount = 0;
    m_msgType = 0;
}

QTankPeerPort::~QTankPeerPort()
{
    close();
}

void QTankPeerPort::sendMsgConnectToC51()
{
    //if(m_conCount)
    //    return;
    m_cmdCount = 0;
    m_msgType = _PEER_CONC51;
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgHeatPress(quint8 stage, quint8 vessel, quint16 press)
{
    m_cmdCount = 0;
    m_msgType = _PEER_HEAT;
    m_heatType = Heat_Press;
    m_heat.setStage(stage);
    m_heat.setVessel(vessel);
    m_heat.setPress(press);
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgHeatStandard(quint8 stage, quint8 vessel, quint16 tempture, quint16 hold)
{
    m_cmdCount = 0;
    m_msgType = _PEER_HEAT;
    m_heatType = Heat_Standart;
    m_heat.setStage(stage);
    m_heat.setVessel(vessel);
    m_heat.setTempture(tempture);
    m_heat.setHold(hold);
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgHeatRAMP(quint8 stage, quint8 vessel,
                                    quint16 ramp, quint16 press, quint16 tempture, quint16 hold)
{
    m_cmdCount = 0;
    m_msgType = _PEER_HEAT;
    m_heatType = Heat_Ramp;
    m_heat.setStage(stage);
    m_heat.setVessel(vessel);
    m_heat.setRamp(ramp);
    m_heat.setPress(press);
    m_heat.setTempture(tempture);
    m_heat.setHold(hold);
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgHeatExtract(quint8 stage, quint16 tempture, quint16 hold)
{
    m_cmdCount = 0;
    m_msgType = _PEER_HEAT;
    m_heatType = Heat_Extract;
    m_heat.setStage(stage);
    m_heat.setTempture(tempture);
    m_heat.setHold(hold);
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgPause()
{
    m_cmdCount = 0;
    m_msgType = _PEER_PAUSE;
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::sendMsgStop()
{
    m_cmdCount = 0;
    m_msgType = _PEER_STOP;
    timer->start(MAX_SERIALTIME);
}

void QTankPeerPort::SendSerialMessage()
{
    if(m_cmdCount > MAX_CONNCOUNT)
    {
        timer->stop();
        m_cmdCount = 0;
        //报警
        pline();
        emit sigPeerException(1);
        return;
    }

    switch(m_msgType)
    {
    case _PEER_CONC51:
        sendConnectToC51();
        break;
    case _PEER_HEAT:
        switch (m_heatType)
        {
        case Heat_Standart:
            sendHeatStandard();
            break;
        case Heat_Ramp:
            sendHeatRAMP();
            break;
        case Heat_Press:
            sendHeatPress();
            break;
        case Heat_Extract:
            sendHeatExtract();
            break;
        default:
            break;
        }
        break;
    case _PEER_PAUSE:
        sendPause();
        break;
    case _PEER_STOP:
        sendStop();
        break;
    }
    m_cmdCount++;
}

void QTankPeerPort::sendConnectToC51()
{
    QTankConnC51Struct t;
    QByteArray l;
    t.pack(l);
    write(l);
    pline() << "connect to c51" << m_cmdCount;
}

void QTankPeerPort::sendHeatPress()
{
    QTankHeatPressStruct t;
    t.setStage(m_heat.stage());
    t.setVessel(m_heat.vessel());
    t.setPress(m_heat.press());
    QByteArray l;
    t.pack(l);
    write(l);
}

void QTankPeerPort::sendHeatStandard()
{
    QTankHeatStandardStruct t;
    t.setStage(m_heat.stage());
    t.setVessel(m_heat.vessel());
    t.setTempture(m_heat.tempture());
    t.setHold(m_heat.hold());
    QByteArray l;
    t.pack(l);
    write(l);
}

void QTankPeerPort::sendHeatRAMP()
{
    QTankHeatRAMPStruct t;
    t.setStage(m_heat.stage());
    t.setVessel(m_heat.vessel());
    t.setRamp(m_heat.ramp());
    t.setPress(m_heat.press());
    t.setTempture(m_heat.tempture());
    t.setHold(m_heat.hold());
    QByteArray l;
    t.pack(l);
    write(l);
}

void QTankPeerPort::sendHeatExtract()
{
    QTankHeatExtractStruct t;
    t.setStage(m_heat.stage());
    t.setTempture(m_heat.tempture());
    t.setHold(m_heat.hold());
    QByteArray l;
    t.pack(l);
    write(l);
}

void QTankPeerPort::sendPause()
{
    QTankPauseStruct t;
    QByteArray l;
    t.pack(l);
    write(l);
}

void QTankPeerPort::sendStop()
{
    QTankStopStruct t;
    QByteArray l;
    t.pack(l);
    write(l);
}


void QTankPeerPort::readyReadData()
{
    // queued conn and queued package;
    // direct conn and ???
    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;
    //TODO:已经具备判断已经接受完全的装备
    do{
        quint16 nBlockLen = QTankPeerMessage::parseBlockSize(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen)
        {
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            //还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
            pline() << "Stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            //TODO:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
            dispatchRecvedMessage(netData);
            continue;
        }
        dispatchRecvedMessage(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}

void QTankPeerPort::updateProgress(qint64)
{

}

void QTankPeerPort::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    QTankPeerMessage qMsg;
    qMsg.parse(blockOnNet);
    pline() << qMsg;
    emit sigRecvMsg(blockOnNet);
    switch(qMsg.cmd())
    {
    case _PEER_CMDNACK:
        recvCmdNAck(qMsg.data());
        break;
    case _PEER_CONC51ACK:
    default:
        pline() << "receive command ack:" << hex << qMsg.cmd();
        recvCmdAck(qMsg.data());
        break;
    }
}

void QTankPeerPort::recvCmdAck(const QByteArray &l)
{
    pline() << "command run success";
    timer->stop();
    //m_conCount = 0;
}

void QTankPeerPort::recvCmdNAck(const QByteArray &l)
{
    pline() << "command run fail";
    // 重发
}

QTankPeerPort *HNPeerPort(QObject *parent)
{
    static QTankPeerPort* com0 = new QTankPeerPort(parent);
    return com0;
}
