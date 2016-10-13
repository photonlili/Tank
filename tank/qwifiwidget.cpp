#include "qwifiwidget.h"
#include "ui_qwifiwidget.h"
#include "qtanklinux.h"
#include "qtankpublic.h"
#include "qtankdefine.h"
#include "hnmsgbox.h"

QWIFIWidget::QWIFIWidget(QWidget *parent) :
    QWIFIView(parent),
    ui(new Ui::QWIFIWidget)
{
    ui->setupUi(this);

    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clickWIFI()), Qt::QueuedConnection);
    m_pass = new QWIFIPassForm(this);

    m_model = new QWIFIModel(this);
    setModel(m_model);
    for(int i = ESSID_TYPE; i < ESSID_MAX; i++)
        setColumnHidden(i, true);
    setColumnWidth(ESSID_STATUS, 40);
}

QWIFIWidget::~QWIFIWidget()
{
    delete ui;
}

void QWIFIWidget::clickWIFI()
{
    QString name = m_model->data(m_model->index(currentIndex().row(), ESSID_NAME)).toString();
    QString encryt = m_model->data(m_model->index(currentIndex().row(), ESSID_ENCRYP)).toString();
    QString type = m_model->data(m_model->index(currentIndex().row(), ESSID_TYPE)).toString();
    QString mac = m_model->data(m_model->index(currentIndex().row(), ESSID_BSSID)).toString();

    HNEthManager::Instance()->setRefresh(false);
    do
    {
        if("YES" == encryt)
        {
            m_pass->setWifiName(name);
            if(QWIFIPassForm::Rejected == m_pass->exec())
                break;
        }

        bool ok = m_model->setCurrentWifi(mac, m_pass->wifiPwd());

        if(!ok)
        {
            HNMsgBox::warning(this, tr("Password error"));
            break;
        }

        pline() << name << encryt << m_pass->wifiPwd();
    }while(0);
    HNEthManager::Instance()->setRefresh();
}

