#ifndef QTANKSERVER_H
#define QTANKSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "hnserialmessage.h"

class QTankServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QTankServer(QObject *parent = 0);
    ~QTankServer();

signals:
    // QTcpServer interface
protected:
    void incomingConnection(int handle);
};

class QTankClientConnection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit QTankClientConnection(QObject *parent = 0);
    ~QTankClientConnection();

signals:

public slots:
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void readyReadData();
};

QTankServer *HNSingleServer(QObject* parent);

#endif // QTANKSERVER_H
