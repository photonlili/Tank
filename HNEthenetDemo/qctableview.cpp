#include "qctableview.h"
#include "ui_qctableview.h"

QCTableView::QCTableView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::QCTableView)
{
    m_header = new QCHeaderView(Qt::Horizontal, this);
    setHorizontalHeader(m_header);
    m_vheader = new QCHeaderView(Qt::Vertical, this);
    setVerticalHeader(m_vheader);

    ui->setupUi(this);
}

QCTableView::~QCTableView()
{
    delete ui;
}

void QCTableView::setObjectName(const QString &name)
{
    QTableView::setObjectName(name);
    m_header->setObjectName(QString("%1_Header").arg(name));
    m_vheader->setObjectName(QString("%1_VHeader").arg(name));
}
