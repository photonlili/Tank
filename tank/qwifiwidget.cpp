#include "qwifiwidget.h"
#include "ui_qwifiwidget.h"
#include "qtanklinux.h"
#include "qtankpublic.h"
#include "qtankdefine.h"

QWIFIWidget::QWIFIWidget(QWidget *parent) :
    QWIFIView(parent),
    ui(new Ui::QWIFIWidget)
{
    ui->setupUi(this);

    m_model = new QWIFIModel(this);
    setModel(m_model);
    for(int i = ESSID_TYPE; i < ESSID_MAX; i++)
        setColumnHidden(i, true);
    setColumnWidth(ESSID_STATUS, 20);
}

QWIFIWidget::~QWIFIWidget()
{
    delete ui;
}

QString QWIFIWidget::currentWIFIName()
{
    return m_model->data(m_model->index(currentIndex().row(), ESSID_NAME)).toString();
}

QString QWIFIWidget::currentWIFIEncrypted()
{
    return m_model->data(m_model->index(currentIndex().row(), ESSID_ENCRYP)).toString();
}

QString QWIFIWidget::currentWIFIType()
{
    return m_model->data(m_model->index(currentIndex().row(), ESSID_TYPE)).toString();
}

QString QWIFIWidget::currentWIFIMAC()
{
    return m_model->data(m_model->index(currentIndex().row(), ESSID_BSSID)).toString();
}

bool QWIFIWidget::setCurrentWifi(QString bssid_mac, QString password)
{
    return m_model->setCurrentWifi(bssid_mac, password);
}
