#include "qtankcrosscenter.h"

QTankCrossCenter::QTankCrossCenter(QObject *parent) :
    QObject(parent)
{
    s0 = HNPeerPort(this);
    s2 = HNSerialPort(this);

    e0 = HNSingleException();
    connect(s0, SIGNAL(sigPeerException(int)), this, SLOT(slotException(int)));
}

void QTankCrossCenter::slotException(int eCode)
{
    pline() ;
    e0->newExcp("GFFFF");
    e0->show();;
}
