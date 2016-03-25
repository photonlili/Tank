#include "hnserver.h"
#include "HNDefine.h"


QTankServer::QTankServer(QObject *parent) :
    QTcpServer(parent)
{
    listen(QHostAddress::Any, 8000);
}

QTankServer::~QTankServer()
{
    close();
}

void QTankServer::incomingConnection(int handle)
{
    QTankClientConnection* clientSocket = new QTankClientConnection(this);
    clientSocket->setSocketDescriptor(handle);
}

QTankClientConnection::QTankClientConnection(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

QTankClientConnection::~QTankClientConnection()
{

}

void QTankClientConnection::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    QTankSerialMessage qMsg;
    qMsg.parse(blockOnNet);
    pline() << qMsg;
}

void QTankClientConnection::readyReadData()
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


QTankServer *HNSingleServer(QObject *parent)
{
    static QTankServer* s = new QTankServer(parent);
    return s;
}

