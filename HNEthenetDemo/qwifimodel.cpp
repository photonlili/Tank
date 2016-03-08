#include "qwifimodel.h"
#include "QSettings"
#include "qtankdefine.h"

QWIFIModel::QWIFIModel(QObject *parent) :
    QCStandardItemModel(parent)
{
    setColumnCount(ESSID_MAX);

    m_pManager = HNEthManager::Instance();
    connect(m_pManager, SIGNAL(sigRefreshed()), this, SLOT(wifiRefreshed()));
}

TWifi QWIFIModel::currentWifi()
{
    return m_pManager->currentWifi();
}

bool QWIFIModel::setCurrentWifi(QString bssid_mac, QString password)
{
    return m_pManager->setCurrentWifi(bssid_mac, password);
}

void QWIFIModel::wifiRefreshed()
{
    int row = 0;
    removeRows(row, rowCount());
    QList<TWifi>& list = m_pManager->wifiList();
    insertRows(row, list.size());
    for(QList<TWifi>::Iterator it = list.begin();
        it != list.end(); it++)
    {
        TWifi wifi = *(TWifi*)(&*it);
        for(int i = ESSID_STATUS; i < ESSID_MAX; i++)
            setData(index(row, i), wifi[i]);
        row++;
    }
    submit();
}
