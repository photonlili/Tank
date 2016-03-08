#ifndef QWIFIMODEL_H
#define QWIFIMODEL_H

#include "qcstandarditemmodel.h"
#include "HNEthManager.h"

class QWIFIModel : public QCStandardItemModel
{
    Q_OBJECT
public:
    explicit QWIFIModel(QObject *parent = 0);

    TWifi currentWifi();
    bool setCurrentWifi(QString bssid_mac, QString password = "");

signals:

public slots:
    void wifiRefreshed();
private:
    HNEthManager* m_pManager;
};

#endif // QWIFIMODEL_H
