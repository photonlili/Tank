#ifndef QTANKSERVER_H
#define QTANKSERVER_H

#include <QTcpServer>

class QTankServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QTankServer(QObject *parent = 0);

signals:

public slots:

};

#endif // QTANKSERVER_H
