#include "qtankserialport.h"
#include "qcomponent.h"

QTankSerialPort::QTankSerialPort(QObject *parent) :
    QSerialPort(parent)
{
#ifdef __MIPS_LINUX__
    QString portName("/dev/ttyS2");
#else
    QString portName("/dev/ttyS2");
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

    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()) );
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
}

QTankSerialPort::~QTankSerialPort()
{
    close();
}

void QTankSerialPort::readyReadData()
{
    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();

    do{
        quint16 nBlockLen = QTankSerialMessage::parseBlockSize(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen)
        {
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            pline() << "Stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            dispatchRecvedMessage(netData);
            continue;
        }
        dispatchRecvedMessage(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}

void QTankSerialPort::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    QTankSerialMessage qMsg;
    qMsg.parse(blockOnNet);
    pline() << qMsg;
    switch(qMsg.cmd())
    {
    case _SERIAL_HAND:
        recvHandup(qMsg.data());
        break;
    case _SERIAL_CLOSE:
        recvClose(qMsg.data());
        break;
    case _SERIAL_WRITEDEVNO:
        recvWriteSerialNumber(qMsg.data());
        break;
    case _SERIAL_READDEVNO:
        recvReadSerial(qMsg.data());
        break;
    case _SERIAL_WRITEPASS:
        recvWritePassword(qMsg.data());
        break;
    case _SERIAL_READPASS:
        recvReadPassword(qMsg.data());
        break;
    default:
        pline() << "receive unknown command:" << hex << qMsg.cmd();
        break;
    }
}

void QTankSerialPort::recvHandup(const QByteArray &l)
{
    sendHandupAck();
}

void QTankSerialPort::sendHandupAck()
{
    //status c51 + local
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QTankHandupAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void QTankSerialPort::recvClose(const QByteArray &l)
{
    sendCloseAck();
}

void QTankSerialPort::sendCloseAck()
{
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QTankCloseAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void QTankSerialPort::recvWriteSerialNumber(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/DeviceNo", l);
    set.sync();
    sendWriteSerialNumberAck();
    emit sigSerialUnlock();
}

void QTankSerialPort::sendWriteSerialNumberAck()
{
    QTankWriteSerialNoAck ack;
    QSettings set;
    QByteArray sn = set.value("/Device/DeviceNo").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void QTankSerialPort::recvReadSerial(const QByteArray &l)
{
    sendReadSerialAck();
}

void QTankSerialPort::sendReadSerialAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/DeviceNo").toByteArray();
    QByteArray l;
    QTankReadSerialNoAck ack;
    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void QTankSerialPort::recvWritePassword(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/Password", l);
    set.sync();
    sendWritePasswordAck();
}

void QTankSerialPort::sendWritePasswordAck()
{
    QTankWritePassAck ack;
    QSettings set;
    QByteArray sn = set.value("/Device/Password").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void QTankSerialPort::  recvReadPassword(const QByteArray &l)
{
    sendReadPasswordAck();
}

void QTankSerialPort::sendReadPasswordAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/Password").toByteArray();
    QByteArray l;
    QTankReadPassAck ack;
    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void QTankSerialPort::sendExceptionAck()
{
    //机器运行出现异常自动通过这个串口上报
    QByteArray l;
    QTankExceptionAck ack;
    //ack.setData("");
    ack.pack(l);
    write(l);
}


QTankSerialPort *HNSerialPort(QObject *parent)
{
    static QTankSerialPort* s2 = new QTankSerialPort(parent);
    return s2;
}
