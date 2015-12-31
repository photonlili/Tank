#ifndef QTANKCROSSCENTER_H
#define QTANKCROSSCENTER_H

#include <QObject>
#include "qtankpeerport.h"
#include "qtankserialport.h"
#include "qtankexception.h"

class QTankCrossCenter : public QObject
{
    Q_OBJECT
public:
    explicit QTankCrossCenter(QObject *parent = 0);

signals:

public slots:
    void slotException(int eCode);

private:
    QTankPeerPort* s0;
    QTankSerialPort* s2;
    QTankException* e0;
};

#endif // QTANKCROSSCENTER_H
